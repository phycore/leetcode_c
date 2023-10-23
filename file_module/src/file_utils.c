#include "file_utils.h"

#include <ctype.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "log.h"

size_t get_file_size(FILE* fp) {
    size_t data_length = 0;
    if (NULL == fp) {
        log_error("File IO stream is null!");
        goto EXIT;
    }

    fseek(fp, 0, SEEK_END);
    data_length = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    log_info("file_size = %zd", data_length);

EXIT:
    return data_length;
}

char* get_file_base_name(const char* file_path) {
    if (NULL == file_path) {
        return NULL;
    }
    char* base_name = strrchr(file_path, (int)PATH_SEP);
    return (base_name != NULL) ? (base_name + 1) : ((char*)file_path);
}

char* get_file_extension_name(const char* file_path) {
    if (NULL == file_path) {
        return NULL;
    }
    return strrchr(file_path, (int)'.');
}

int read_file_to_buffer(FILE* fp, unsigned char* file_buffer, size_t* file_data_length) {
    file_utility_return_t retval = FILE_UTILITY_SUCCESS;
    size_t read_size = 0;

    if (NULL == fp) {
        log_error("File IO stream is null!");
        retval = FILE_UTILITY_FILE_STREAM_INVALID;
        goto EXIT;
    }

    if (0 == *file_data_length) {
        log_error("Give string buffer lenth is wrong!");
        retval = FILE_UTILITY_PARAMS_INCOREECT;
        goto EXIT;
    }

    read_size = fread(file_buffer, sizeof(unsigned char), *file_data_length, fp);
    *file_data_length = read_size;

EXIT:
    return retval;
}

int read_file_to_string(FILE* fp, unsigned char* file_in_string, size_t* file_in_string_length) {
    file_utility_return_t retval = FILE_UTILITY_SUCCESS;

    if (NULL == fp) {
        log_error("File IO stream is null!");
        retval = FILE_UTILITY_FILE_STREAM_INVALID;
        goto EXIT;
    }

    if (0 == *file_in_string_length) {
        log_error("Give string buffer lenth is wrong!");
        retval = FILE_UTILITY_PARAMS_INCOREECT;
        goto EXIT;
    }

    int ch = '0';
    int idx = 0;
    size_t examine_length = *file_in_string_length;
    while ((ch = fgetc(fp)) != EOF) {
        if ((isspace((unsigned char)ch)) || ((unsigned char)ch == '\n')) {
            continue;
        }
        *(file_in_string + idx) = (unsigned char)ch;
        idx++;

        // Exception handler!
        if (idx > examine_length) {
            log_error(
                "Give initial allocate file_in_string_length = %zd too samll to store string!",
                examine_length);
            retval = FILE_UTILITY_OUT_BUFFER_SIZE_INSUFFICIENT;
            // break;
            goto EXIT;
        }
    }
    *(file_in_string + idx) = '\0';

    size_t data_length = strlen(file_in_string);
    *file_in_string_length = data_length;

EXIT:
    return retval;
}