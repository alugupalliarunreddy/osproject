#ifndef TRANSLATE_H
#define TRANSLATE_H
#include "vmem.h"
int translate_address(VmManager *vm, uint16_t virtual_address,
                      uint16_t *physical_address);
#endif
