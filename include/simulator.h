#ifndef SIMULATOR_H
#define SIMULATOR_H
#include "vmem.h"
int simulator_init(VmManager *vm, size_t pages, size_t frames, VmPolicy policy);
void simulator_tables(const VmManager *vm);
void simulator_reset(VmManager *vm);
#endif
