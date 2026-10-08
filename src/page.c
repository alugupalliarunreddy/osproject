#include "page.h"
#include <stddef.h>

void page_table_reset(VmManager *vm)
{
    for (size_t i = 0; i < vm->page_count; ++i) {
        vm->pages[i].valid = 0;
        vm->pages[i].frame = -1;
        vm->pages[i].loaded_at = 0;
        vm->pages[i].last_used = 0;
    }
}

int page_is_valid(const VmManager *vm, unsigned page)
{
    return page < vm->page_count && vm->pages[page].valid;
}

void page_map(VmManager *vm, unsigned page, int frame)
{
    vm->pages[page].valid = 1;
    vm->pages[page].frame = frame;
    vm->pages[page].loaded_at = vm->clock;
    vm->pages[page].last_used = vm->clock;
}

void page_unmap(VmManager *vm, unsigned page)
{
    vm->pages[page].valid = 0;
    vm->pages[page].frame = -1;
}
