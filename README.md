# Virtual Memory Management Utility — OSSP Week 2

Working Week 2 milestone: interactive REPL with dynamically allocated input.

**Scope:** This is the foundation for the Virtual Memory Management Utility. Page tables, virtual-to-physical address translation, and page replacement are not implemented yet.

## Build and run (Ubuntu/WSL)
Install tools if needed:
```bash
sudo apt update
sudo apt install build-essential python3
```
From this folder:
```bash
make clean
make
make run
```
Run the long-input test:
```bash
make test
```
Commands: `help`, `status`, `exit`, `quit`. Other input is echoed, including long lines.
