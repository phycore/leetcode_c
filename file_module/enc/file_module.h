#ifndef _FILE_MODULE_H
#define _FILE_MODULE_H

#include <stdint.h>

#include "file_module_base.h"

typedef enum {
    FILE_MODULE_SUCCESS = 0,
    FILE_MODULE_IFACE_INVALID,
    FILE_MODULE_CONTEXT_INVALID,
    FILE_MODULE_MAKE_INSTANCE_FAIL,
    FILE_MODULE_INSTANCE_INVALID,
    FILE_MODULE_INCORRECT_PARAM,
    FILE_MODULE_OUT_OF_MEMORY,
} file_module_return_t;

typedef enum { GET_STR_RESERVED = 0, GET_STR_BASE_NAME = 1, GET_STR_EXTENSION = 2 } ifile_get_str_t;

typedef enum {
    GET_INT_RESERVED = 0,
    GET_INT_FILE_SIZE = 1,
    GET_INT_FILE_CONTENTS_BUFFER_LEN = 2,
    GET_INT_FILE_CONTENTS_STR_LEN = 3
} ifile_get_int_t;

typedef enum {
    GET_BUFFER_RESERVED = 0,
    GET_BUFFER_CONTENTS = 1,
    GET_BUFFER_CONTENTS_STRING = 2
} ifile_get_buff_t;

typedef struct file_handle {
    void* context;
    IFILE_HANDLE_BASE(file_handle);
} ifile_handle_t;

ifile_handle_t* create_file_handle(void);
int32_t destroy_file_handle(ifile_handle_t* p_ifile_handle);

#endif  // _FILE_MODULE_H