# Virtual Memory Management Utility (VMU)

A command-line virtual memory simulator written in C that demonstrates address translation, page faults, page tables, and FIFO/LRU page-replacement algorithms.

**Operating Systems and Systems Programming (OSSP) Project**

![Language](https://img.shields.io/badge/Language-C-blue)
![Platform](https://img.shields.io/badge/Platform-Linux%20%7C%20Ubuntu-orange)
![Build](https://img.shields.io/badge/Build-GNU%20Make-green)
![Project](https://img.shields.io/badge/Type-Educational%20Simulator-purple)

## Overview

The Virtual Memory Management Utility (VMU) is a terminal-based educational simulator designed to demonstrate fundamental virtual memory management concepts used in operating systems.

The project models how virtual addresses are translated into physical addresses, how page tables maintain page mappings, and how page faults are handled when a requested page is not currently loaded into physical memory.

The simulator is implemented in C using dynamically allocated data structures and a modular design.

> **Note:** VMU is a user-space simulation. It does not access or modify the host operating system's actual page tables, physical memory, or kernel memory.

## Features

* **Virtual address translation:** Converts virtual addresses into physical addresses using page numbers, offsets, and frame mappings.
* **Page table management:** Tracks page presence and frame assignments.
* **Page-fault handling:** Simulates loading pages into free frames and handling memory replacement when frames are full.
* **FIFO replacement:** Implements the First-In, First-Out page-replacement algorithm.
* **LRU replacement:** Implements the Least Recently Used page-replacement algorithm.
* **Configurable memory:** Supports configurable virtual pages, physical frames, and page sizes.
* **Interactive CLI:** Provides commands to access addresses, inspect memory state, view statistics, and reset the simulator.
* **Dynamic input handling:** Uses dynamically allocated input buffers instead of fixed-size input arrays.
* **Memory statistics:** Tracks accesses, page faults, hits, evictions, and page-fault rate.

## Technology Stack

| Component            | Technology                                   |
| -------------------- | -------------------------------------------- |
| Programming language | C                                            |
| Compiler             | GCC                                          |
| Build system         | GNU Make                                     |
| Operating system     | Linux / Ubuntu                               |
| Input handling       | Standard C I/O and dynamic memory allocation |

## Architecture

The project follows a modular structure that separates the command-line interface, input handling, and virtual memory simulation logic.

```text
                 User
                  |
                  v
          Command-Line Interface
                main.c
                  |
          +-------+-------+
          |               |
          v               v
      input.c          vmem.c
   Input Handling   Memory Simulator
                          |
               +----------+----------+
               |                     |
               v                     v
          Page Table            Frame Table
               |                     |
               +----------+----------+
                          |
                          v
             Address Translation
              and Replacement
```

### Module Responsibilities

| Module    | Responsibility                                                                                          |
| --------- | ------------------------------------------------------------------------------------------------------- |
| `main.c`  | Handles command parsing, startup configuration, and the interactive interface.                          |
| `input.c` | Reads input lines using dynamically allocated memory.                                                   |
| `vmem.c`  | Implements page tables, frame management, address translation, page faults, and replacement algorithms. |
| `vmem.h`  | Defines simulator data structures and public function declarations.                                     |
| `input.h` | Declares the dynamic input interface.                                                                   |

## Virtual Memory Concepts

### 1. Address Translation

A virtual address is divided into a virtual page number and an offset.

```text
Virtual Address = Page Number × Page Size + Offset
```

The simulator calculates:

```c
page_number = virtual_address / page_size;
offset = virtual_address % page_size;
```

If the page is present in a physical frame, the physical address is calculated as:

```c
physical_address = frame_number * page_size + offset;
```

### 2. Page Table

The page table maintains information about each virtual page, including:

* Whether the page is currently present in physical memory.
* The physical frame containing the page.
* The page's load timestamp.
* The page's last-used timestamp.

### 3. Page Faults

A page fault occurs when a valid virtual address references a page that is not currently loaded into a physical frame.

The simulator handles this by:

1. Identifying the requested virtual page.
2. Searching for an available physical frame.
3. Loading the page into a free frame if one exists.
4. Otherwise, selecting a victim page using the configured replacement policy.
5. Updating the page table and frame table.
6. Calculating and displaying the physical address.

### 4. Page-Replacement Algorithms

| Algorithm | Description                                                        |
| --------- | ------------------------------------------------------------------ |
| FIFO      | Replaces the resident page that was loaded earliest.               |
| LRU       | Replaces the resident page whose most recent access is the oldest. |

FIFO uses page load timestamps, while LRU uses logical access timestamps.

These implementations are simplified educational models and do not represent all the mechanisms used by production operating systems.

## Project Structure

```text
osproject/
├── include/
│   ├── input.h
│   └── vmem.h
├── src/
│   ├── input.c
│   ├── main.c
│   └── vmem.c
├── tests/
│   └── smoke_test.sh
├── docs/
│   └── DESIGN.md
├── Makefile
├── .gitignore
└── README.md
```

## Getting Started

### Prerequisites

The following tools are required:

* GCC or another C11-compatible compiler.
* GNU Make.
* Bash for the smoke test.

On Ubuntu, install the dependencies:

```bash
sudo apt update
sudo apt install build-essential make git -y
```

### Clone the Repository

```bash
git clone https://github.com/alugupalliarunreddy/osproject.git
cd osproject
```

### Build the Project

Compile the source code from the project root:

```bash
make clean
make
```

The executable is generated at:

```text
bin/vmem
```

### Run the Simulator

```bash
./bin/vmem
```

Alternatively, compile and launch the program using:

```bash
make run
```

## Usage

After launching the simulator, the interactive command prompt appears:

```text
Virtual Memory Management Utility
Educational user-space simulator; does not alter real OS memory.
Type 'help' to see available commands.
vm>
```

### Example Session

```text
vm> status
vm> access 0
vm> access 4096
vm> access 8192
vm> access 0
vm> pages
vm> frames
vm> stats
vm> exit
```

The default configuration consists of:

| Parameter          | Default Value |
| ------------------ | ------------: |
| Virtual pages      |            16 |
| Physical frames    |             4 |
| Page size          |    4096 bytes |
| Replacement policy |          FIFO |

### Custom Configuration

The simulator accepts command-line arguments to configure the virtual memory environment.

```bash
./bin/vmem --pages 32 --frames 3 --page-size 1024
```

This creates a virtual address space with 32 pages, 3 physical frames, and a page size of 1024 bytes.

Configuration requirements:

* The number of virtual pages must be greater than zero.
* The number of physical frames must be greater than zero and no greater than the number of virtual pages.
* The page size must be a positive power of two.

## Command Reference

| Command          | Description                                                          |
| ---------------- | -------------------------------------------------------------------- |
| `help`           | Displays the available commands.                                     |
| `status`         | Displays simulator configuration and the current replacement policy. |
| `access ADDRESS` | Accesses and translates a virtual address.                           |
| `pages`          | Displays the virtual page table.                                     |
| `frames`         | Displays the physical frame table.                                   |
| `stats`          | Displays memory access and page-fault statistics.                    |
| `policy fifo`    | Selects FIFO replacement.                                            |
| `policy lru`     | Selects LRU replacement.                                             |
| `reset`          | Clears memory mappings and resets statistics.                        |
| `exit`           | Exits the simulator.                                                 |
| `quit`           | Exits the simulator.                                                 |

Addresses must be entered as non-negative decimal integers. Addresses outside the configured virtual address space are rejected.

## Testing

The project includes a basic shell-based smoke test.

Run:

```bash
make test
```

The test exercises basic address accesses, page-fault output, replacement-policy selection, statistics, and reset behavior.

Expected successful output:

```text
Smoke test passed.
```

This is a lightweight smoke test and does not constitute exhaustive validation of every possible input or memory configuration.

## Build Configuration

The Makefile uses GCC with C11 support and common warning flags:

```makefile
-std=c11 -Wall -Wextra -Wpedantic -Werror
```

To remove generated object files and the executable:

```bash
make clean
```

To rebuild the project:

```bash
make
```

## Limitations

VMU is an educational simulator and has the following limitations:

* It does not implement actual kernel-level virtual memory management.
* It does not perform real disk-backed paging or swap operations.
* It does not implement hardware-level TLB translation.
* It does not implement multi-level page tables.
* It does not provide process isolation or real memory protection.
* It does not simulate concurrent memory accesses.

The simulated page tables and physical frames exist only within the program's allocated memory.

## Future Enhancements

Potential extensions include:

* Implementing a simulated backing store with swap-in and swap-out operations.
* Adding a Translation Lookaside Buffer (TLB) with hit and miss statistics.
* Supporting multi-level page tables.
* Implementing read/write permissions and protection faults.
* Adding file-based memory reference sequences for repeatable experiments.
* Implementing additional page-replacement algorithms, such as Clock.
* Providing graphical visualization of page tables, frames, and page faults.

## Contributing

Contributions, suggestions, and bug reports are welcome.

To contribute:

1. Fork the repository.
2. Create a feature branch.
3. Implement and test your changes.
4. Submit a pull request with a clear description of the changes.

Please ensure that your changes compile successfully and that the existing smoke test passes.

## License

No license has been specified for this repository yet. Add a `LICENSE` file before granting others explicit permission to use, modify, or redistribute the project.

---

*Developed as an educational project to explore virtual memory management and operating system concepts using C.*
