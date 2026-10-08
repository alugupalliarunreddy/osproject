#include "translate.h"
#include "page.h"
#include "frame.h"
#include "replacement.h"

int translate_address(VmManager *vm, uint16_t virtual_address,
                      uint16_t *physical_address)
{
    if (vm == NULL || physical_address == NULL) return -1;

    unsigned page = virtual_address / VM_PAGE_SIZE;
    unsigned offset = virtual_address % VM_PAGE_SIZE;
    if (page >= vm->page_count) return -1;

    ++vm->clock;
    ++vm->accesses;

    if (!page_is_valid(vm, page)) {
        ++vm->page_faults;
        int frame = replacement_choose(vm);

        if (vm->frames[frame].occupied) {
            unsigned old_page = (unsigned)vm->frames[frame].page;
            page_unmap(vm, old_page);
            ++vm->evictions;
        }

        frame_load(vm, (unsigned)frame, page);
        page_map(vm, page, frame);
    }

    int frame = vm->pages[page].frame;
    vm->pages[page].last_used = vm->clock;
    vm->frames[frame].last_used = vm->clock;

    *physical_address =
        (uint16_t)((unsigned)frame * VM_PAGE_SIZE + offset);
    return 0;
}
