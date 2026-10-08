#ifndef PAGE_H
#define PAGE_H
#include "vmem.h"
void page_table_reset(VmManager *vm);
int page_is_valid(const VmManager *vm, unsigned page);
void page_map(VmManager *vm, unsigned page, int frame);
void page_unmap(VmManager *vm, unsigned page);
#endif
