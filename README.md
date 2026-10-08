# Virtual Memory Management Utility (VMU)

A modular Unix/Linux C11 project that simulates core operating-system virtual memory concepts.

VMU is structured as a multi-module OS project, with separate components for input handling, command parsing, page management, frame management, replacement policies, address translation, statistics, and simulator control.

> VMU is an educational user-space simulator. It does not replace or modify the Linux kernel memory-management subsystem.

## Project Progress

### Week 1 – Project Setup and CLI
- C11 project structure
- Modular source/header organization
- Interactive VM prompt
- GNU Make build system

### Week 2 – Input and Command Parser
- Interactive input handling
- Command parsing
- `read`, `tables`, `stats`, `reset`, `help`, and `quit`

### Week 3 – Page and Frame Management
- Page table representation
- Physical frame table
- Valid-bit management
- Page-to-frame mapping

### Week 4 – Address Translation
- Page-number extraction
- Offset extraction
- Page-table lookup
- Physical-address generation

### Week 5 – Page Fault Handling
- Page-fault detection
- Loading pages into frames
- Frame eviction
- Fault and eviction counters

### Week 6 – FIFO Page Replacement
- First-In First-Out policy
- Load-time tracking
- Victim-frame selection

### Week 7 – LRU Page Replacement
- Least Recently Used policy
- Access-time tracking
- Victim selection based on recent use

### Week 8 – Statistics and Analysis
- Access count
- Page-fault count
- Eviction count
- Fault-rate calculation

### Week 9 – Testing and Debugging
- Strict GCC warnings
- Automated smoke test
- AddressSanitizer build target
- Defensive validation

### Week 10 – Final Integration
- Complete modular VM simulator
- Documentation
- Reproducible build
- Final CLI integration

## Current Features

- Interactive virtual-memory simulator
- Virtual-to-physical address translation
- Page table
- Frame table
- Page-fault simulation
- FIFO page replacement
- LRU page replacement
- Page eviction
- Memory statistics
- Fault-rate calculation
- Simulator reset
- Modular C11 implementation
- Make-based build system
- Smoke testing
- AddressSanitizer support

## Example Usage

```text
==========================================
 Virtual Memory Management Utility (VMU)
==========================================
Number of virtual pages (1-256): 4
Number of physical frames (1-16): 2
Replacement policy (FIFO/LRU): FIFO

Commands:
  read <address>  Translate a virtual address
  tables          Display page and frame tables
  stats           Display memory statistics
  reset           Reset the simulator
  help            Display commands
  quit            Exit
```

Example:

```text
vm> read 0
VA 0 -> PA 0

vm> read 256
VA 256 -> PA 256

vm> read 512
VA 512 -> PA 0

vm> stats

Memory Statistics
-----------------
Accesses: 3
Page faults: 3
Evictions: 1
Fault rate: 100.00%
```

## Build Instructions

```bash
make
```

Run:

```bash
make run
```

Test:

```bash
make test
```

Clean:

```bash
make clean
```

AddressSanitizer:

```bash
make asan
```

## Project Structure

```text
VirtualMemoryManagementUtility/
├── include/
│   ├── vmem.h
│   ├── input.h
│   ├── parser.h
│   ├── page.h
│   ├── frame.h
│   ├── replacement.h
│   ├── translate.h
│   ├── stats.h
│   └── simulator.h
│
├── src/
│   ├── input.c
│   ├── main.c
│   ├── parser.c
│   ├── page.c
│   ├── frame.c
│   ├── replacement.c
│   ├── translate.c
│   ├── stats.c
│   └── simulator.c
│
├── .gitignore
├── Makefile
└── README.md
```

## Source Module Responsibilities

| Module | Responsibility |
|---|---|
| `main.c` | Main VM application and CLI loop |
| `input.c` | Safe interactive input |
| `parser.c` | Command parsing |
| `page.c` | Page-table operations |
| `frame.c` | Physical-frame operations |
| `replacement.c` | FIFO/LRU victim selection |
| `translate.c` | Address translation and page faults |
| `stats.c` | Memory statistics |
| `simulator.c` | VM initialization, tables and reset |

## Memory Model

```text
Virtual Address
      |
      v
+-------------+
| Page Number |
+-------------+
|   Offset    |
+-------------+
      |
      v
  Page Table
      |
      v
 Frame Number
      |
      v
Physical Address
```

The simulator uses a page size of 256 bytes, supports up to 256 virtual pages, and up to 16 physical frames.

## Replacement Policies

### FIFO

The oldest loaded page is selected as the victim.

### LRU

The page that has been unused for the longest period is selected as the victim.

## Objective

The project provides a practical implementation of virtual-memory concepts normally handled by an operating system, allowing students to observe page tables, frames, page faults, address translation, and replacement policies through a controlled simulation.

## Academic Scope

Developed as an Operating Systems and System Programming educational project using C11 on Linux/Ubuntu.

## License

For academic and educational use.
