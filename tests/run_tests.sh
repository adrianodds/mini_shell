#!/usr/bin/env bash
set -eu

MINI=./minishell
TMPDIR="tests_tmp"
rm -rf "$TMPDIR"
mkdir -p "$TMPDIR"
fail=0

run_test_file() {
  name="$1"
  input_file="$2"
  expected_file="$3"

  cat "$input_file" | $MINI > "$TMPDIR/out.txt" 2>&1 || true
  if diff -u "$expected_file" "$TMPDIR/out.txt" >/dev/null 2>&1; then
    echo "PASS: $name"
  else
    echo "FAIL: $name"
    echo "--- EXPECTED ($expected_file) ---"
    sed -n '1,200p' "$expected_file"
    echo "--- GOT ---"
    sed -n '1,200p' "$TMPDIR/out.txt"
    fail=1
  fi
}

run_dynamic() {
  name="$1"
  input_file="$2"
  expected_text="$3"
  cat "$input_file" | $MINI > "$TMPDIR/out.txt" 2>&1 || true
  printf '%b' "$expected_text" > "$TMPDIR/exp_dynamic.exp"
  if diff -u "$TMPDIR/exp_dynamic.exp" "$TMPDIR/out.txt" >/dev/null 2>&1; then
    echo "PASS: $name"
  else
    echo "FAIL: $name"
    echo "--- EXPECTED ---"
    sed -n '1,200p' "$TMPDIR/exp_dynamic.exp"
    echo "--- GOT ---"
    sed -n '1,200p' "$TMPDIR/out.txt"
    fail=1
  fi
}

# Test 1: assignment simple
cat > "$TMPDIR/exp_assignment_simple" <<'EOF'
1
EOF
cat > "$TMPDIR/in_assignment_simple" <<'INPUT'
VAR=1
echo $VAR
exit
INPUT
run_test_file "assignment_simple" "$TMPDIR/in_assignment_simple" "$TMPDIR/exp_assignment_simple"

# Test 2: inline assignment
cat > "$TMPDIR/exp_assignment_inline" <<'EOF'
9
EOF
cat > "$TMPDIR/in_assignment_inline" <<'INPUT'
VARX=9
echo $VARX
exit
INPUT
run_test_file "assignment_inline" "$TMPDIR/in_assignment_inline" "$TMPDIR/exp_assignment_inline"

# Test 3: escaped dollar
cat > "$TMPDIR/exp_escaped_dollar" <<'EOF'
$VAR
EOF
cat > "$TMPDIR/in_escaped_dollar" <<'INPUT'
VAR=5
echo \$VAR
exit
INPUT
run_test_file "escaped_dollar" "$TMPDIR/in_escaped_dollar" "$TMPDIR/exp_escaped_dollar"

# Test 4: pid $$ (dynamic check)
out=$(printf '%s' "$(cat <<'IN'
 echo $$
 exit
IN
)" | $MINI 2>&1 || true)
if echo "$out" | grep -qE '^[0-9]+$'; then
  echo "PASS: pid_dollar"
else
  echo "FAIL: pid_dollar"
  echo "GOT:"; echo "$out"
  fail=1
fi

# Test 5: heredoc basic
cat > "$TMPDIR/exp_heredoc_basic" <<'EOF'
hello
EOF
cat > "$TMPDIR/in_heredoc_basic" <<'INPUT'
cat << EOF
hello
EOF
exit
INPUT
run_test_file "heredoc_basic" "$TMPDIR/in_heredoc_basic" "$TMPDIR/exp_heredoc_basic"

# Test 6: pipe uppercase
cat > "$TMPDIR/exp_pipe_tr" <<'EOF'
HELLO
EOF
cat > "$TMPDIR/in_pipe_tr" <<'INPUT'
echo hello | tr a-z A-Z
exit
INPUT
run_test_file "pipe_tr" "$TMPDIR/in_pipe_tr" "$TMPDIR/exp_pipe_tr"

# Test 7: redirection out
cat > "$TMPDIR/exp_redir_out" <<'EOF'
hi
EOF
cat > "$TMPDIR/in_redir_out" <<INPUT
echo hi > $TMPDIR/outfile
cat $TMPDIR/outfile
exit
INPUT
run_test_file "redir_out" "$TMPDIR/in_redir_out" "$TMPDIR/exp_redir_out"

# Test 8: unclosed quote
cat > "$TMPDIR/exp_unclosed_quote" <<'EOF'
minishell: syntax error: unclosed quote
EOF
cat > "$TMPDIR/in_unclosed_quote" <<'INPUT'
echo "unclosed
INPUT
run_test_file "unclosed_quote" "$TMPDIR/in_unclosed_quote" "$TMPDIR/exp_unclosed_quote"

# Test 9: consecutive pipe
cat > "$TMPDIR/exp_consecutive_pipe" <<'EOF'
minishell: syntax error: pipe
EOF
cat > "$TMPDIR/in_consecutive_pipe" <<'INPUT'
echo || echo
exit
INPUT
run_test_file "consecutive_pipe" "$TMPDIR/in_consecutive_pipe" "$TMPDIR/exp_consecutive_pipe"

# Test 10: echo no args
cat > "$TMPDIR/exp_echo_nothing" <<'EOF'

EOF
cat > "$TMPDIR/in_echo_no_args" <<'INPUT'
echo
exit
INPUT
run_test_file "echo_no_args" "$TMPDIR/in_echo_no_args" "$TMPDIR/exp_echo_nothing"

# Test 11: echo -n
printf 'no_newline' > "$TMPDIR/exp_echo_n"
cat > "$TMPDIR/in_echo_n" <<'INPUT'
echo -n no_newline
exit
INPUT
run_test_file "echo_n" "$TMPDIR/in_echo_n" "$TMPDIR/exp_echo_n"

# Test 12: single quotes prevent expansion
cat > "$TMPDIR/exp_single_quote" <<'EOF'
$VAR
EOF
cat > "$TMPDIR/in_single_quote" <<'INPUT'
VAR=42
echo '$VAR'
exit
INPUT
run_test_file "single_quote_no_expand" "$TMPDIR/in_single_quote" "$TMPDIR/exp_single_quote"

# Test 13: double quotes allow expansion
cat > "$TMPDIR/exp_double_quote" <<'EOF'
42
EOF
cat > "$TMPDIR/in_double_quote" <<'INPUT'
VAR=42
echo "$VAR"
exit
INPUT
run_test_file "double_quote_expand" "$TMPDIR/in_double_quote" "$TMPDIR/exp_double_quote"

# Test 14: escaped quote inside double quotes
cat > "$TMPDIR/exp_escaped_quote" <<'EOF'
he"llo
EOF
cat > "$TMPDIR/in_escaped_quote" <<'INPUT'
echo "he\"llo"
exit
INPUT
run_test_file "escaped_quote_in_double" "$TMPDIR/in_escaped_quote" "$TMPDIR/exp_escaped_quote"

# Test 15: command not found
cat > "$TMPDIR/exp_cmd_nf" <<'EOF'
minishell: nosuchcmd: command not found
EOF
cat > "$TMPDIR/in_cmd_nf" <<'INPUT'
nosuchcmd
exit
INPUT
run_test_file "cmd_not_found" "$TMPDIR/in_cmd_nf" "$TMPDIR/exp_cmd_nf"

# Test 16: exit status propagation (false -> 1)
cat > "$TMPDIR/exp_exit_status" <<'EOF'
1
EOF
cat > "$TMPDIR/in_exit_status" <<'INPUT'
false
echo $?
exit
INPUT
run_test_file "exit_status_false" "$TMPDIR/in_exit_status" "$TMPDIR/exp_exit_status"

# Test 17: builtin in pipeline (echo | wc -c)
cat > "$TMPDIR/in_builtin_pipe" <<'INPUT'
echo -n hello | wc -c
exit
INPUT
exp_wc=$(echo -n hello | wc -c)
run_dynamic "builtin_in_pipe" "$TMPDIR/in_builtin_pipe" "$exp_wc\n"

# Test 18: append redir
cat > "$TMPDIR/exp_append" <<'EOF'
line1
line2
EOF
cat > "$TMPDIR/in_append" <<INPUT
echo line1 > $TMPDIR/afile
echo line2 >> $TMPDIR/afile
cat $TMPDIR/afile
exit
INPUT
run_test_file "append_redir" "$TMPDIR/in_append" "$TMPDIR/exp_append"

# Test 19: multiple pipes chain
cat > "$TMPDIR/exp_multi_pipe" <<'EOF'
X
EOF
cat > "$TMPDIR/in_multi_pipe" <<'INPUT'
echo x | tr a-z A-Z | tr A-Z X
exit
INPUT
run_test_file "multi_pipe" "$TMPDIR/in_multi_pipe" "$TMPDIR/exp_multi_pipe"

# Test 20: heredoc with quoted delimiter (no expansion)
cat > "$TMPDIR/exp_heredoc_quoted" <<'EOF'
$VAR
EOF
cat > "$TMPDIR/in_heredoc_quoted" <<'INPUT'
VAR=123
cat << 'EOF'
$VAR
EOF
exit
INPUT
run_test_file "heredoc_quoted_no_expand" "$TMPDIR/in_heredoc_quoted" "$TMPDIR/exp_heredoc_quoted"

# Test 21: whitespace preservation inside quotes
cat > "$TMPDIR/exp_spaces" <<'EOF'
a  b
EOF
cat > "$TMPDIR/in_spaces" <<'INPUT'
echo "a  b"
exit
INPUT
run_test_file "spaces_in_quotes" "$TMPDIR/in_spaces" "$TMPDIR/exp_spaces"

# Test 22: export sets variable
cat > "$TMPDIR/exp_export_set" <<'EOF'
8
EOF
cat > "$TMPDIR/in_export_set" <<'INPUT'
export ETEST=8
echo $ETEST
exit
INPUT
run_test_file "export_set" "$TMPDIR/in_export_set" "$TMPDIR/exp_export_set"

# Test 23: unset removes variable
cat > "$TMPDIR/exp_unset" <<'EOF'

EOF
cat > "$TMPDIR/in_unset" <<'INPUT'
VAR=9
unset VAR
echo $VAR
exit
INPUT
run_test_file "unset_var" "$TMPDIR/in_unset" "$TMPDIR/exp_unset"

# Test 24: escaped dollar inside double quotes
cat > "$TMPDIR/exp_escaped_dollar_double" <<'EOF'
a$VAR
EOF
cat > "$TMPDIR/in_escaped_dollar_double" <<'INPUT'
VAR=5
echo "a\$VAR"
exit
INPUT
run_test_file "escaped_dollar_in_double" "$TMPDIR/in_escaped_dollar_double" "$TMPDIR/exp_escaped_dollar_double"

# Test 25: redirection input with temporary file creation
cat > "$TMPDIR/exp_redir_in" <<'EOF'
content_in
EOF
cat > "$TMPDIR/in_redir_in" <<INPUT
cat > $TMPDIR/myin <<EOF
content_in
EOF
cat < $TMPDIR/myin
exit
INPUT
run_test_file "redir_in" "$TMPDIR/in_redir_in" "$TMPDIR/exp_redir_in"

# finished
if [ "$fail" -eq 0 ]; then
  echo "ALL TESTS PASSED"
else
  echo "SOME TESTS FAILED"
fi
exit $fail
