#include "frame.h"
#include <stddef.h>

void frame_table_reset(VmManager *vm)
{
    for (size_t i = 0; i < vm->frame_count; ++i) {
        vm->frames[i].occupied = 0;
        vm->frames[i].page = -1;
        vm->frames[i].loaded_at = 0;
        vm->frames[i].last_used = 0;
    }
}

int frame_find_free(const VmManager *vm)
{
    for (size_t i = 0; i < vm->frame_count; ++i)
        if (!vm->frames[i].occupied) return (int)i;
    return -1;
}

void frame_load(VmManager *vm, unsigned frame, unsigned page)
{
    vm->frames[frame].occupied = 1;
    vm->frames[frame].page = (int)page;
    vm->frames[frame].loaded_at = vm->clock;
    vm->frames[frame].last_used = vm->clock;
}

void frame_clear(VmManager *vm, unsigned frame)
{
    vm->frames[frame].occupied = 0;
    vm->frames[frame].page = -1;
    vm->frames[frame].loaded_at = 0;
    vm->frames[frame].last_used = 0;
}
