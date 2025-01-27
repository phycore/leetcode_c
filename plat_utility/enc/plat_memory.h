#ifndef _PLAT_MEM_H
#define _PLAT_MEM_H

#include <stdio.h>
#include <stdlib.h>

#define PLAT_FREE(p) plat_free((void**)&(p))

void* plat_allocate(size_t alloc_size);
void plat_free(void** pp_memory);

#endif  // _PLAT_MEM_H