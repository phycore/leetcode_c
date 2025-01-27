#include "plat_memory.h"

void* plat_allocate(size_t alloc_size) {
    void* p_raw_memory = (void*)malloc(alloc_size);
    return p_raw_memory;
}

void plat_free(void** pp_memory) {
    if (NULL != pp_memory && NULL != (*pp_memory)) {
        free(*pp_memory);
        *pp_memory = NULL;
    }
}