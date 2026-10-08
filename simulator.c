#include "simulator.h"
#include "page.h"
#include "frame.h"
#include <stdio.h>
#include <string.h>

int simulator_init(VmManager *vm, size_t pages, size_t frames, VmPolicy policy)
{
    if (vm == NULL || pages == 0 || pages > VM_MAX_PAGES ||
        frames == 0 || frames > VM_MAX_FRAMES) return -1;

    memset(vm, 0, sizeof(*vm));
    vm->page_count = pages;
    vm->frame_count = frames;
    vm->policy = policy;
    page_table_reset(vm);
    frame_table_reset(vm);
    return 0;
}

void simulator_tables(const VmManager *vm)
{
    puts("\nPage Table");
    puts("Page | Valid | Frame");
    puts("-----+-------+------");
    for (size_t i = 0; i < vm->page_count; ++i)
        printf("%4zu | %5d | %5d\n", i, vm->pages[i].valid,
               vm->pages[i].valid ? vm->pages[i].frame : -1);

    puts("\nFrame Table");
    puts("Frame | Occupied | Page");
    puts("------+----------+-----");
    for (size_t i = 0; i < vm->frame_count; ++i)
        printf("%5zu | %8d | %4d\n", i, vm->frames[i].occupied,
               vm->frames[i].occupied ? vm->frames[i].page : -1);
}

void simulator_reset(VmManager *vm)
{
    uint64_t accesses = 0;
    (void)accesses;
    size_t pages = vm->page_count;
    size_t frames = vm->frame_count;
    VmPolicy policy = vm->policy;
    (void)simulator_init(vm, pages, frames, policy);
}
