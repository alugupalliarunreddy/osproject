# OS Project

This project is developed as part of the Operating Systems and Systems Programming (OSSP) Project-Based Learning course.

## Week 1 Features
- Interactive REPL loop
- Makefile-based build
- Git repository
- Linux development environment

## Week 2 Features
- Dynamic command input
- Memory allocation using malloc()
- Automatic buffer expansion using realloc()
- Proper memory cleanup using free()

## Project Structure

```text
osproject/
├── README.md
├── Makefile
├── .gitignore
├── include/
│   ├── shell.h
│   └── input.h
├── src/
│   ├── main.c
│   └── input.c
├── docs/
├── tests/
├── screenshots/
└── bin/
```

## Build

```bash
make clean
make
```

## Run

```bash
make run
```

## Clean

```bash
make clean
```

## Week 2 Milestone

Implemented dynamic input using heap memory with malloc() and realloc(),
and released allocated memory using free().
