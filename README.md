# ft_sh2

`ft_sh2` is a small interactive Unix shell written in C. It was built as a
42-style systems project and includes its own line editor, environment handling,
command history, and a local `libft` dependency.

The shell runs in raw terminal mode so it can read keys directly, redraw the
current input line, move the cursor, and browse command history.

## Features

- Interactive prompt with termcap-based terminal control.
- Execution of commands found through `PATH`.
- Execution of commands by direct path, for example `/bin/ls`.
- Built-in commands:
  - `cd`
  - `setenv`
  - `unsetenv`
  - `exit`
- Basic line editing:
  - printable character insertion
  - backspace deletion
  - left and right arrow cursor movement
  - up and down arrow history navigation
- Persistent command history stored in `.history` in the project directory.
- Signal handling for common terminal signals.

## Requirements

- A Unix-like system.
- `make`
- A C compiler compatible with the project flags, such as `cc` or `clang`.
- Termcap support, linked with `-ltermcap`.

The project was primarily written for a 42/macOS-style environment. On some
Linux distributions, you may need to install the development package that
provides termcap or ncurses compatibility.

## Build

Build the shell:

```sh
make
```

Clean object files:

```sh
make clean
```

Remove object files and the executable:

```sh
make fclean
```

Rebuild from scratch:

```sh
make re
```

The build produces the executable:

```sh
./ft_sh2
```

## Run

Start the shell from the project root:

```sh
./ft_sh2
```

You should see a welcome line and then the prompt:

```text
$>
```

Exit the shell with:

```sh
exit
```

## Examples

Run external commands:

```sh
ls
pwd
/bin/echo hello
```

Change directory:

```sh
cd /tmp
pwd
cd -
cd ~
```

Edit the environment:

```sh
setenv MY_VAR hello
unsetenv MY_VAR
```

Use history:

```text
Up arrow     previous command
Down arrow   next command
```

Move around the current command line:

```text
Left arrow   move cursor left
Right arrow  move cursor right
Backspace    delete character before the cursor
Enter        execute command
```

## Project Layout

```text
.
├── includes/       public project header
├── libft/          custom C utility library
├── src/            shell source files
├── Makefile        project build rules
└── auteur          author file
```

Important source areas:

- `src/main.c`: shell startup and main input loop.
- `src/funct.c`: command dispatch, external execution, and built-ins.
- `src/eb_term.c`: terminal raw-mode setup and restore.
- `src/eb_list*.c`: editable command-line buffer.
- `src/eb_cmd.c`: command history storage and loading.
- `src/eb_env*.c`: environment copy, lookup, update, and deletion.
- `src/eb_signal.c`: signal registration and handling.

## Limitations

This is a learning shell, not a full POSIX shell implementation.

Current parsing is intentionally simple:

- Arguments are split on spaces.
- Quoting and escaping are not implemented.
- Pipes are not implemented.
- Redirections are not implemented.
- Command chaining with `;`, `&&`, or `||` is not implemented.
- Environment variable expansion, such as `$HOME`, is not implemented.

## Notes

The shell writes history to `.history` in the current working directory. If you
run `ft_sh2` from the project root, that file will be created beside the
Makefile.

Because the program changes terminal settings while it runs, always exit with
`exit` when possible. If the terminal display becomes inconsistent after an
unexpected stop, running `reset` in the parent shell usually restores it.
