# Simple Shell

This is a simple UNIX command interpreter (shell) created as a project for ALX Software Engineering program. The shell mimics the basic functionality of the `/bin/sh` shell.

## Overview

The Simple Shell project aims to create a basic command-line interpreter in C language. The shell allows users to execute commands, manage processes, and manipulate the environment. It is designed to adhere to the specifications provided by ALX SE, ensuring proper compilation, coding style, and functionality.

## Features

- Executes commands entered by the user.
- Supports input/output redirection.
- Handles background processes.
- Implements basic built-in commands (`exit`, `cd`).
- Error handling and reporting.

## Requirements

- Allowed editors: vi, vim, emacs
- Compiled on Ubuntu 20.04 LTS using gcc with the options `-Wall -Werror -Wextra -pedantic -std=gnu89`
- Code follows the Betty style guidelines
- No memory leaks
- Limited to 5 functions per file
- Use of system calls only when necessary
- Proper README.md and AUTHORS files
- Collaborate via a single GitHub repository
- Mimic output and error messages of `/bin/sh`

## Usage

To compile the Simple Shell, use the following command:

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh

To run the shell in interactive mode, execute:
./hsh
To run the shell in non-interactive mode, use input redirection:
echo "command" | ./hsh

Examples
Interactive mode:
$ ./hsh
($) /bin/ls
README.md hsh.c main.c shell.c
($) echo "Hello, World!"
Hello, World!
($) exit

Non-interactive mode:
$ echo "/bin/ls" | ./hsh
README.md hsh.c main.c shell.c

Authors
Your Name
Hind HAJJI

License
This project is licensed under the MIT License - see the LICENSE file for details.
