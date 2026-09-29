# Virtual Memory Management Utility

An educational user-space simulator demonstrating virtual-to-physical address translation, page faults, page/frame tables, and FIFO/LRU page replacement. It does not modify or manage the host operating system's actual virtual memory.

## Build and run

```bash
make clean
make
make run
```

Enter the number of virtual pages, number of physical frames, and FIFO or LRU replacement policy. At the `vm>` prompt, use `read <address>`, `tables`, `stats`, `reset`, `help`, or `quit`.

Run the smoke test with `make test`.

Each page is 256 bytes. The simulator supports up to 256 virtual pages and 16 physical frames.
