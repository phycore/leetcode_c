#ifndef _VEC_STORING_POOL_H
#define _VEC_STORING_POOL_H

#include <stdint.h>

// TODO: storing multi dimentional vector. ex: [ [1, 2, 3], [4, 5, 6]]

#define MAX_SIZE_VEC (uint32_t)0xFFFF

typedef enum {
    VEC_TYPE_STR = 1,
    VEC_TYPE_INT = 2,
} vec_type_t;

typedef enum {
    VEC_STORING_SUCCESS,
    VEC_STORING_NO_VEC_TYPE,
    VEC_STORING_NO_ALLOC,
    VEC_STORING_OUT_OF_MEMORY,
    VEC_STORING_BUFFER_OVERFLOW,
    VEC_STORING_READ_FAIL,
} vector_storing_return_t;

int32_t init_vector_storing(void);
int32_t uninit_vector_storing(void);

void* allocate_vector(vec_type_t vec_type);
int32_t free_vector(vec_type_t vec_type);
int32_t clear_vector(vec_type_t vec_type);

int32_t push_vector(vec_type_t vec_type, void* push_value);
// TODO: push vector array.

#endif  // _VEC_STORING_POOL_H