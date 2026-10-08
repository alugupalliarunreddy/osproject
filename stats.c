#include "stats.h"
#include <stdio.h>

void stats_print(const VmManager *vm)
{
    double rate = vm->accesses
        ? (double)vm->page_faults / (double)vm->accesses * 100.0
        : 0.0;

    puts("\nMemory Statistics");
    puts("-----------------");
    printf("Accesses: %llu\n", (unsigned long long)vm->accesses);
    printf("Page faults: %llu\n", (unsigned long long)vm->page_faults);
    printf("Evictions: %llu\n", (unsigned long long)vm->evictions);
    printf("Fault rate: %.2f%%\n", rate);
}
