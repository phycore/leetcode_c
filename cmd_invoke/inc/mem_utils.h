#ifndef _MEM_UTILS_H
#define _MEM_UTILS_H

#include <stdio.h>

#define SAFE_FREE(ptr)     \
    do {                   \
        if (NULL != ptr) { \
            free(ptr);     \
            ptr = NULL;    \
        }                  \
    } while (0)

char** new_char_list(size_t list_length, size_t key_length);
void delete_char_list(char** list, size_t list_length);

#endif  // _MEM_UTILS_H