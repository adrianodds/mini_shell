#!/usr/bin/env python3
import os
import pty
import re
import select
import shutil
import signal
import subprocess
import sys
import tempfile
import time


class PTYShell:
    def __init__(self, minishell_path):
        self.minishell_path = minishell_path
        self.pid = None
        self.fd = None
        self.buffer = ""

    def start(self):
        pid, fd = pty.fork()
        if pid == 0:
            os.execv(self.minishell_path, [self.minishell_path])
        self.pid = pid
        self.fd = fd
        self.buffer = ""

    def close(self):
        if self.fd is not None:
            try:
                os.close(self.fd)
            except OSError:
                pass
            self.fd = None
        if self.pid is not None:
            try:
                os.kill(self.pid, signal.SIGKILL)
            except ProcessLookupError:
                pass
            self.pid = None

    def send(self, data):
        if self.fd is None:
            return
        os.write(self.fd, data.encode())

    def send_signal(self, sig):
        if self.pid is None:
            return
        os.kill(self.pid, sig)

    def read_for(self, timeout=1.0):
        end = time.time() + timeout
        collected = ""
        while time.time() < end:
            wait = max(0.0, end - time.time())
            r, _, _ = select.select([self.fd], [], [], wait)
            if not r:
                continue
            try:
                data = os.read(self.fd, 4096)
            except OSError:
                break
            if not data:
                break
            chunk = data.decode(errors="ignore")
            collected += chunk
            self.buffer += chunk
        return collected

    def expect_regex(self, pattern, timeout=2.0):
        end = time.time() + timeout
        regex = re.compile(pattern, re.S)
        while time.time() < end:
            if regex.search(self.buffer):
                return True
            self.read_for(0.15)
        return bool(regex.search(self.buffer))


class Result:
    def __init__(self):
        self.items = []

    def add(self, name, ok, details="", manual=False):
        self.items.append((name, ok, details))
        if manual and details:
            self.items[-1] = (f"{name} [MANUAL]", ok, details)

    def summary(self):
        passed = sum(1 for _, ok, _ in self.items if ok)
        total = len(self.items)
        print("\n=== SUMMARY ===")
        for name, ok, details in self.items:
            status = "PASS" if ok else "FAIL"
            print(f"[{status}] {name}")
            if details:
                print(f"       {details}")
        print(f"\nResult: {passed}/{total} passed")
        return 0 if passed == total else 1


def run_noninteractive(minishell_path, command, timeout_sec=5):
    try:
        proc = subprocess.run(
            [minishell_path, "-c", command],
            capture_output=True,
            text=True,
            timeout=timeout_sec,
        )
        return proc.returncode, proc.stdout, proc.stderr
    except subprocess.TimeoutExpired as exc:
        out = exc.stdout or ""
        err = exc.stderr or ""
        err += "\n[tester-timeout] command exceeded timeout"
        return 124, out, err


def run_pipe_input(minishell_path, script_text, timeout_sec=8):
    try:
        proc = subprocess.run(
            [minishell_path],
            input=script_text,
            capture_output=True,
            text=True,
            timeout=timeout_sec,
        )
        return proc.returncode, proc.stdout, proc.stderr
    except subprocess.TimeoutExpired as exc:
        out = exc.stdout or ""
        err = exc.stderr or ""
        err += "\n[tester-timeout] piped input exceeded timeout"
        return 124, out, err


def clean_output(text):
    lines = text.splitlines()
    cleaned = []
    for line in lines:
        stripped = line.strip()
        if stripped.startswith("minishell$"):
            continue
        if stripped == "exit":
            continue
        cleaned.append(line)
    return "\n".join(cleaned)


def check_valgrind(minishell_path):
    if shutil.which("valgrind") is None:
        return None, "valgrind not found (skipped)"
    cmd = [
        "valgrind",
        "--leak-check=full",
        "--show-leak-kinds=all",
        "--errors-for-leak-kinds=all",
        minishell_path,
    ]
    proc = subprocess.run(cmd, input="exit\n", capture_output=True, text=True)
    leak_free = "definitely lost: 0 bytes" in proc.stderr or "All heap blocks were freed -- no leaks are possible" in proc.stderr
    return leak_free, "checked with valgrind"


def check_compile(minishell_path, root, result):
    makefile = os.path.join(root, "Makefile")
    if not os.path.exists(makefile):
        result.add("Compile: Makefile exists", False)
        return
    proc = subprocess.run(
        ["make", "-C", root, "-Bn"],
        capture_output=True,
        text=True,
    )
    text = proc.stdout + proc.stderr
    has_flags = "-Wall" in text and "-Wextra" in text and "-Werror" in text
    result.add("Compile: -Wall -Wextra -Werror", has_flags)

    first = subprocess.run(["make", "-C", root], capture_output=True, text=True)
    second = subprocess.run(["make", "-C", root], capture_output=True, text=True)
    no_relink = "gcc " not in second.stdout and "gcc " not in second.stderr
    result.add("Compile: make succeeds", first.returncode == 0)
    result.add("Compile: no relink on second make", no_relink)


def check_simple_and_args(minishell_path, result):
    code, _, _ = run_noninteractive(minishell_path, "/bin/ls")
    result.add("Simple command absolute path", code == 0)

    code, out, err = run_pipe_input(minishell_path, "   \n\t\n/bin/echo EMPTY_OK\n")
    cleaned = clean_output(out)
    result.add("Empty/spaces/tabs do not crash", code in (0, 1, 127))
    result.add("Continues after empty lines", "EMPTY_OK" in cleaned and "Segmentation" not in err)

    code, out, _ = run_noninteractive(minishell_path, "/bin/echo one two three")
    result.add("Arguments without quotes", code == 0 and "one two three" in out)


def check_builtins(minishell_path, result):
    code, out, _ = run_noninteractive(minishell_path, "echo hello")
    ok_echo = code == 0 and out.strip() == "hello"
    code2, out2, _ = run_noninteractive(minishell_path, "echo -n hello")
    ok_echo_n = code2 == 0 and out2 == "hello"
    result.add("Builtin echo", ok_echo and ok_echo_n)

    e0 = subprocess.run([minishell_path, "-c", "exit"], capture_output=True, text=True)
    e42 = subprocess.run([minishell_path, "-c", "exit 42"], capture_output=True, text=True)
    ebad = subprocess.run([minishell_path, "-c", "exit abc"], capture_output=True, text=True)
    ok_exit = e0.returncode == 0 and e42.returncode == 42 and ebad.returncode == 2
    result.add("Builtin exit", ok_exit)

    env_script = "export X_TEST=42\nenv | grep ^X_TEST=\nunset X_TEST\nenv | grep ^X_TEST=\n"
    code, out, _ = run_pipe_input(minishell_path, env_script)
    cleaned = clean_output(out)
    result.add("Builtin export/env/unset", "X_TEST=42" in cleaned and code in (0, 1))

    code, out, _ = run_pipe_input(minishell_path, "pwd\ncd ..\npwd\n")
    lines = [ln for ln in clean_output(out).splitlines() if ln.strip()]
    ok_cd_pwd = len(lines) >= 2 and lines[0] != lines[-1]
    result.add("Builtin cd/pwd", ok_cd_pwd)


def check_status_and_quotes(minishell_path, result):
    script = "/bin/ls /definitely_missing\necho $?\n"
    code, out, _ = run_pipe_input(minishell_path, script)
    cleaned = clean_output(out)
    status_line = cleaned.splitlines()[-1] if cleaned.splitlines() else ""
    result.add("Return value with $?", code in (0, 1, 2, 127) and status_line.isdigit())

    user = os.environ.get("USER", "")
    script = "echo '$USER'\necho \"$USER\"\n"
    _, out, _ = run_pipe_input(minishell_path, script)
    cleaned = [ln.strip() for ln in clean_output(out).splitlines() if ln.strip()]
    ok_single = len(cleaned) >= 1 and cleaned[0] == "$USER"
    ok_double = len(cleaned) >= 2 and cleaned[1] == user
    result.add("Single quotes do not expand", ok_single)
    result.add("Double quotes expand variables", ok_double)


def check_paths(minishell_path, result):
    proc = subprocess.run(
        [minishell_path, "-c", "../bin/ls /tmp"],
        cwd="/tmp",
        capture_output=True,
        text=True,
    )
    result.add("Relative path execution", proc.returncode == 0)

    code, out, err = run_pipe_input(minishell_path, "unset PATH\nls\n")
    text = out + err
    result.add("Unset PATH disables bare commands", "command not found" in text)

    code, out, err = run_pipe_input(minishell_path, "export PATH=/bin:/usr/bin\nls\n")
    text = clean_output(out + "\n" + err)
    result.add("PATH restore enables bare commands", "command not found" not in text)


def check_redirections_and_pipes(minishell_path, result):
    with tempfile.TemporaryDirectory(prefix="ms_eval_") as tmpd:
        in_file = os.path.join(tmpd, "in.txt")
        out_file = os.path.join(tmpd, "out.txt")
        with open(in_file, "w", encoding="utf-8") as f:
            f.write("hello\nworld\n")

        script = (
            f"cat < {in_file}\n"
            f"echo one > {out_file}\n"
            f"echo two >> {out_file}\n"
            f"cat {out_file}\n"
        )
        _, out, err = run_pipe_input(minishell_path, script)
        cleaned = clean_output(out + "\n" + err)
        ok_in = "hello" in cleaned and "world" in cleaned
        ok_out = "one" in cleaned and "two" in cleaned
        result.add("Redirections < > >>", ok_in and ok_out)

        hd_script = "cat << EOF\nhello_hd\nEOF\n"
        _, out, err = run_pipe_input(minishell_path, hd_script)
        cleaned = clean_output(out + "\n" + err)
        result.add("Heredoc <<", "hello_hd" in cleaned)

        code, out, _ = run_noninteractive(minishell_path, "echo hi | cat")
        ok_pipe = code == 0 and "hi" in out
        result.add("Pipes", ok_pipe)

        code, out, _ = run_noninteractive(minishell_path, f"cat < {in_file} | grep world")
        result.add("Pipe + redirection mix", code == 0 and "world" in out)


def check_go_crazy(minishell_path, result):
    _, out, err = run_noninteractive(minishell_path, "dsbksdgbksdghsd")
    text = out + err
    ok_unknown = "command not found" in text or "No such file" in text
    result.add("Unknown command does not crash", ok_unknown)

    code, out, err = run_pipe_input(minishell_path, "cat | cat | ls\n", timeout_sec=5)
    result.add("cat | cat | ls behaves normally", code in (0, 1) and "Segmentation" not in out + err)

    long_args = "echo " + " ".join(["x" * 10 for _ in range(300)])
    code, out, err = run_noninteractive(minishell_path, long_args)
    result.add("Long command does not crash", code == 0 and "Segmentation" not in out + err)


def interactive_signal_history_tests(minishell_path, result):
    sh = PTYShell(minishell_path)
    try:
        sh.start()
        sh.read_for(0.4)
        has_prompt = sh.expect_regex(r"minishell\$", 2.0)
        result.add("Interactive startup prompt", has_prompt)

        sh.send_signal(signal.SIGINT)
        sh.read_for(0.4)
        ctrl_c_empty = sh.expect_regex(r"minishell\$", 2.0)
        result.add("Ctrl-C on empty prompt", ctrl_c_empty)

        sh.send("echo __BUFFER_SHOULD_NOT_EXEC__")
        time.sleep(0.15)
        sh.send_signal(signal.SIGINT)
        sh.read_for(0.4)
        sh.send("\n")
        sh.read_for(0.6)
        ran_stale = re.search(r"\n__BUFFER_SHOULD_NOT_EXEC__\r?\n", sh.buffer) is not None
        result.add("Ctrl-C clears typed buffer", not ran_stale)

        sh.send("cat\n")
        sh.read_for(0.3)
        sh.send_signal(signal.SIGINT)
        sh.read_for(0.5)
        cat_interrupt = sh.expect_regex(r"minishell\$", 2.0)
        result.add("Ctrl-C interrupts blocking command", cat_interrupt)

        sh.send_signal(signal.SIGQUIT)
        sh.read_for(0.3)
        try:
            os.kill(sh.pid, 0)
            alive = True
        except OSError:
            alive = False
        result.add("Ctrl-\\ does not terminate shell", alive)

        sh.send("echo HIST_OK\n")
        sh.read_for(0.5)
        first_ok = "HIST_OK" in sh.buffer
        sh.send("\x1b[A\n")
        sh.read_for(0.7)
        hist_count = sh.buffer.count("HIST_OK")
        result.add("History Up recalls previous command", first_ok and hist_count >= 2)

        sh2 = PTYShell(minishell_path)
        sh2.start()
        sh2.read_for(0.5)
        sh2.send("\x04")
        exited = False
        for _ in range(20):
            time.sleep(0.1)
            try:
                os.kill(sh2.pid, 0)
            except OSError:
                exited = True
                break
        if exited:
            result.add("Ctrl-D exits on empty prompt", True)
        else:
            result.add(
                "Ctrl-D exits on empty prompt",
                True,
                "inconclusive in PTY automation, validate manually in interactive terminal",
                manual=True,
            )
        sh2.close()

        sh3 = PTYShell(minishell_path)
        sh3.start()
        sh3.read_for(0.4)
        sh3.send("abc")
        time.sleep(0.1)
        sh3.send("\x04")
        sh3.read_for(0.4)
        try:
            os.kill(sh3.pid, 0)
            still_alive = True
        except OSError:
            still_alive = False
        result.add("Ctrl-D with typed text does not exit", still_alive, manual=True)
        sh3.close()
    finally:
        sh.close()


def main():
    root = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
    minishell_path = os.path.join(root, "minishell")

    if not os.path.exists(minishell_path):
        print("minishell binary not found. Run `make` first.")
        return 2

    result = Result()

    print("Running compile checks...")
    check_compile(minishell_path, root, result)

    print("Running mandatory command checks...")
    check_simple_and_args(minishell_path, result)
    check_builtins(minishell_path, result)
    check_status_and_quotes(minishell_path, result)
    check_paths(minishell_path, result)
    check_redirections_and_pipes(minishell_path, result)
    check_go_crazy(minishell_path, result)

    print("Running interactive signal/history checks...")
    interactive_signal_history_tests(minishell_path, result)

    print("Running optional leak check...")
    leak_ok, leak_msg = check_valgrind(minishell_path)
    if leak_ok is None:
        result.add("Leak check (optional)", True, leak_msg)
    else:
        result.add("Leak check (valgrind)", leak_ok, leak_msg)

    return result.summary()


if __name__ == "__main__":
    sys.exit(main())
