# Linux System Programming Projects

This repository contains various Linux system programming exercises and implementations. It is an ongoing project with regular additions.

## Overview

The repo currently includes:

- **srivya** - A custom shell implementation supporting:
  - Built-in `cd` command with HOME directory support
  - External command execution via `fork()` and `execvp()`
  - Output redirection using `>`
  - Interactive prompt (`srivvya> `)

- **process_playground** - Demonstrates `fork()` usage, showing parent/child process PID relationships

- **program** - A compiled executable

- Supporting source files and documentation

## Building

Compile the C source files using `gcc`:

```bash
gcc srivya.c -o srivya
gcc process_playground.c -o process_playground
```

## Running

```bash
./srivya
# Inside the shell:
cd        - change directory
        > output.txt  - redirect output to file
```

## Roadmap

- Add more built-in commands (exit, help, etc.)
- Implement piping and background processes
- Add command history
- Expand test coverage