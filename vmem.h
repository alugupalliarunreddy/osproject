#ifndef VMEM_H
#define VMEM_H
#include <stddef.h>
#include <stdint.h>

#define VM_PAGE_SIZE 256u
#define VM_MAX_PAGES 256u
#define VM_MAX_FRAMES 16u

typedef enum { VM_FIFO, VM_LRU } VmPolicy;

typedef struct {
    int valid;
    int frame;
    uint64_t loaded_at;
    uint64_t last_used;
} PageEntry;

typedef struct {
    int occupied;
    int page;
    uint64_t loaded_at;
    uint64_t last_used;
} FrameEntry;

typedef struct {
    size_t page_count;
    size_t frame_count;
    VmPolicy policy;
    PageEntry pages[VM_MAX_PAGES];
    FrameEntry frames[VM_MAX_FRAMES];
    uint64_t clock;
    uint64_t accesses;
    uint64_t page_faults;
    uint64_t evictions;
} VmManager;

#endif
