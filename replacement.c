#include "replacement.h"
#include "frame.h"
#include <stddef.h>

int replacement_choose(const VmManager *vm)
{
    int free_frame = frame_find_free(vm);
    if (free_frame >= 0) return free_frame;

    size_t victim = 0;
    uint64_t oldest = vm->policy == VM_FIFO
        ? vm->frames[0].loaded_at : vm->frames[0].last_used;

    for (size_t i = 1; i < vm->frame_count; ++i) {
        uint64_t stamp = vm->policy == VM_FIFO
            ? vm->frames[i].loaded_at : vm->frames[i].last_used;
        if (stamp < oldest) {
            oldest = stamp;
            victim = i;
        }
    }
    return (int)victim;
}
