#ifndef _FILE_UTILS_H
#define _FILE_UTILS_H

#include <stdio.h>

#include "plat_string.h"

typedef enum {
    FILE_UTILITY_SUCCESS = 0,
    FILE_UTILITY_FILE_STREAM_INVALID = 1,
    FILE_UTILITY_PARAMS_INCOREECT = 2,
    FILE_UTILITY_OUT_BUFFER_SIZE_INSUFFICIENT = 3
} file_utility_return_t;

size_t get_file_size(FILE* fp);
char* get_file_base_name(const char* file_path);
char* get_file_extension_name(const char* file_path);
int read_file_to_buffer(FILE* fp, unsigned char* file_buffer, size_t* file_data_length);
int read_file_to_string(FILE* fp, unsigned char* file_in_string, size_t* file_in_string_length);

#endif  // _FILE_UTILS_H