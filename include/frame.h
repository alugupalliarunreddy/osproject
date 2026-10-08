#ifndef FRAME_H
#define FRAME_H
#include "vmem.h"
void frame_table_reset(VmManager *vm);
int frame_find_free(const VmManager *vm);
void frame_load(VmManager *vm, unsigned frame, unsigned page);
void frame_clear(VmManager *vm, unsigned frame);
#endif
