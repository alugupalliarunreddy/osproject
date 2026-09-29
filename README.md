# Virtual Memory Management Utility (VMU)

**Operating Systems and Systems Programming (OSSP) Project**  
**Language:** C (C11)  
**Platform:** Linux / Ubuntu  
**Build system:** GNU Make

## 1. Project overview

The Virtual Memory Management Utility is a terminal-based educational simulator that demonstrates how an operating system translates virtual addresses into physical addresses and handles page faults when a requested page is not currently loaded in physical memory.

This is a user-space simulation. It does **not** read or modify the host operating system's real page tables, physical memory, or kernel memory. Instead, it models the key concepts using C data structures.

The utility currently supports:

- Configurable page size and number of physical frames.
- A virtual address space divided into pages.
- Page-table entries that track whether a page is present and which frame contains it.
- Virtual-to-physical address translation.
- Page-fault counting.
- FIFO and LRU page-replacement policies.
- Interactive commands to inspect status, access addresses, change policy, and reset the simulator.
- Input validation and dynamically allocated input storage.

## 2. Concepts demonstrated

### Virtual address

A virtual address is split into two components:

`virtual address = virtual page number × page size + offset`

The simulator computes:

- `page_number = virtual_address / page_size`
- `offset = virtual_address % page_size`

If the page is resident in a physical frame, the physical address is:

`physical_address = frame_number × page_size + offset`

### Page table

Each virtual page has a page-table entry. An entry records whether the page is present, its frame number when present, and metadata used by the replacement algorithm.

### Page fault

A page fault occurs in this simulator when an address references a valid virtual page that is not currently resident in a physical frame. The simulator loads the page into a free frame, or evicts a resident page according to the selected replacement policy.

### Replacement policies

- **FIFO (First-In, First-Out):** evicts the page that has been resident for the longest time.
- **LRU (Least Recently Used):** evicts the page whose most recent access is oldest.

These policies are simplified educational models, not implementations of a production kernel's memory manager.

## 3. Requirements

On Ubuntu or a similar Linux distribution:

- GCC or another C11-compatible compiler
- GNU Make
- Bash (for the optional shell test script)

Install the tools:

```bash
sudo apt update
sudo apt install build-essential make
```

## 4. Build and run

From the project root:

```bash
make clean
make
./bin/vmem
```

Or build and launch in one command:

```bash
make run
```

Run the basic automated smoke test:

```bash
make test
```

The test exercises address translation, replacement-policy commands, status output, and reset behavior. It is a lightweight smoke test, not a formal proof of correctness.

## 5. First session

Start the program:

```text
$ ./bin/vmem
Virtual Memory Management Utility
Type 'help' to see available commands.
vm> help
```

Try the following sequence:

```text
vm> status
vm> access 0
vm> access 4096
vm> access 8192
vm> access 0
vm> policy lru
vm> access 12288
vm> pages
vm> frames
vm> stats
vm> exit
```

The default configuration is 16 virtual pages, 4 physical frames, and 4096-byte pages. These values are configurable at startup:

```bash
./bin/vmem --pages 32 --frames 3 --page-size 1024
```

The number of virtual pages must be positive, the number of frames must be positive and no greater than the number of virtual pages, and the page size must be a positive power of two. The simulator uses unsigned integer addresses.

## 6. Interactive command reference

| Command | Description |
|---|---|
| `help` | Print the command list. |
| `status` | Show configuration, current policy, and counters. |
| `access ADDRESS` | Translate and access a decimal virtual address. |
| `pages` | Show each virtual page's presence and frame mapping. |
| `frames` | Show the virtual page currently stored in each physical frame. |
| `stats` | Show accesses, page faults, hits, and evictions. |
| `policy fifo` | Select FIFO replacement. |
| `policy lru` | Select LRU replacement. |
| `reset` | Clear page/frame state and counters. |
| `help` | Display help. |
| `exit` or `quit` | Exit the utility. |

Addresses are entered as decimal non-negative integers. An address outside the configured virtual address space is rejected.

## 7. Project structure

```text
VirtualMemoryUtility_Full_Project/
├── include/
│   ├── input.h       # Dynamic line-input interface
│   └── vmem.h        # VM types and public simulator functions
├── src/
│   ├── input.c       # Safe dynamically growing input reader
│   ├── main.c        # CLI, command parsing, and startup options
│   └── vmem.c        # Page table, frames, translation, FIFO/LRU
├── tests/
│   └── smoke_test.sh # Basic command-line smoke test
├── docs/
│   └── DESIGN.md     # Design notes and algorithms
├── Makefile
├── .gitignore
└── README.md
```

## 8. Design and implementation notes

The command-line interface is kept separate from the memory simulator. `main.c` reads and parses commands, while `vmem.c` owns the simulated memory state and implements translation and replacement. `input.c` handles input lines without relying on a fixed-size buffer.

The simulator allocates the page table and frame table dynamically. Allocation failures are reported and cleaned up. The simulator rejects invalid configuration values and invalid addresses rather than silently wrapping them.

### Access algorithm

1. Validate that the requested virtual address is in range.
2. Compute the virtual page number and page offset.
3. If the page-table entry is present, count a hit and update LRU metadata.
4. Otherwise, count a page fault.
5. Use a free frame if one exists; otherwise choose a victim according to FIFO or LRU and evict it.
6. Map the requested page into the selected frame.
7. Compute and print the physical address.

### FIFO details

Each successful page load receives an increasing load-order value. When memory is full, FIFO selects the resident page with the smallest load-order value. A hit does not change its FIFO age.

### LRU details

Each access receives an increasing logical timestamp. On a hit or load, the page's last-used timestamp is updated. When memory is full, LRU selects the resident page with the smallest last-used timestamp.

## 9. Example output

Exact counters and victim pages depend on the commands entered and the chosen policy.

```text
vm> access 0
PAGE FAULT: virtual page 0 loaded into frame 0
Virtual address: 0
Page number:     0
Offset:          0
Frame number:    0
Physical address: 0
```

## 10. Troubleshooting

### `make: command not found`

Install Make and the compiler:

```bash
sudo apt update
sudo apt install build-essential make
```

### `./bin/vmem: No such file or directory`

Build the program from the project root:

```bash
make
```

### `Permission denied` for the test

Run:

```bash
chmod +x tests/smoke_test.sh
make test
```

### Want to rebuild from scratch

```bash
make clean
make
```

## 11. GitHub workflow

If you already cloned your repository, extract/copy the project files into that repository folder. Preserve the existing `.git` directory. Then:

```bash
git status
git add README.md Makefile .gitignore include src tests docs
git commit -m "Implement virtual memory simulator"
git push
```

If Git reports that there is no upstream branch, use the branch name shown by `git branch --show-current`:

```bash
git push -u origin "$(git branch --show-current)"
```

Do not put passwords, access tokens, or private credentials in the repository.

## 12. Scope and future improvements

This project is a teaching simulator. It does not implement kernel-level demand paging, disk-backed swap, TLB hardware, multi-level page tables, process isolation, concurrency, or actual OS memory protection. Possible future extensions include:

- Simulated backing store and swap-in/swap-out.
- A TLB cache and hit/miss statistics.
- Multi-level page tables.
- Read/write permissions and protection faults.
- A workload file for repeatable reference strings.
- Additional replacement algorithms such as Clock.

## 13. Academic note

Use this README as project documentation and make sure you understand the source code before demonstrating or submitting it. Follow your course's rules for permitted assistance and disclose external assistance if your instructor requires it.
