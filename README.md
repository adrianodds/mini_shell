*This project was created as part of the 42 curriculum by adduarte.*

# Minishell

## Description
**Minishell** is a minimal Unix shell implementation written in C, inspired by core Bash behavior. The main goal of this project is to practice fundamental operating system and low-level programming concepts such as:

- process creation and management (`fork`, `execve/execvp`, `wait`);
- redirections and pipes;
- input parsing with quote handling and variable expansion;
- environment management (`envp`);
- interactive signal handling.

In short, this project reproduces the core shell cycle: **read**, **parse**, and **execute** commands, with support for builtins and external commands.

## Instructions

### Build
From the repository root, run:

```bash
make
```

Useful maintenance commands:

```bash
make clean
make fclean
make re
```

### Run
After building:

```bash
./minishell
```

### Usage Examples

```bash
echo "hello"
export USER_TEST=42
echo $USER_TEST
ls -la | grep minishell
cat < infile > outfile
```

## Resources

### Technical References
- Bash Reference Manual: https://www.gnu.org/software/bash/manual/
- POSIX Shell Command Language: https://pubs.opengroup.org/onlinepubs/9699919799/
- Linux man pages:
   - `readline`, `signal`, `fork`, `execve`, `wait`, `pipe`, `dup2`, `open`, `close`
- 42 Minishell subject and official project documentation.

### AI Usage in This Project
AI was used as a **support tool** for specific engineering and documentation tasks, without replacing conceptual understanding:

- reviewing and reorganizing code structure (module separation);
- assisting with refactors to improve readability and maintainability;
- helping validate compile issues and diagnose regressions;
- supporting the writing and formatting of this `README.md`.

## Project Structure

```text
.
├── include/
├── src/
│   ├── core/
│   ├── parsing/
│   ├── execution/
│   ├── builtins/
│   ├── env/
│   ├── utils/
│   └── libft/
├── minishell.h
└── Makefile
```
