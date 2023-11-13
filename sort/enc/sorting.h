#ifndef _SORTING_H
#define _SORTING_H

#include <stdint.h>
#include <stdio.h>

typedef int32_t (*sort_fn)(int32_t*, size_t);

int32_t bubble_sort(int32_t* p_array, size_t size);
int32_t selection_sort(int32_t* p_array, size_t size);

#endif