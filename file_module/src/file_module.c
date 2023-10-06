#include "file_module.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file_utils.h"
#include "log.h"

#define FREE(ptr)      \
    if (NULL != ptr) { \
        free(ptr);     \
    }                  \
    ptr = NULL

typedef struct file_contents {
    unsigned char* buffer;
    size_t size;
} file_contents_t;

typedef struct file_data {
    FILE* fp;
    size_t size;
    char* base_name;
    char* ext_name;
    file_contents_t contents_buffer;
    file_contents_t contents_string;
} file_data_t;

static int32_t check_file_handle(ifile_handle_t* p_ifile_handle);

static int file_handle_set_impl(ifile_handle_t* p_ifile_handle);

static int32_t file_handle_init_impl(ifile_handle_t* p_ifile_handle);
static int32_t file_handle_uninit_impl(ifile_handle_t* p_ifile_handle);
static int32_t file_handle_make_instance_impl(ifile_handle_t* p_ifile_handle, char* file_path);
static int32_t file_handle_get_base_version_impl(ifile_handle_t* p_ifile_handle,
                                                 char* base_version);
static int32_t file_handle_get_string_impl(ifile_handle_t* p_ifile_handle, int32_t str_type,
                                           char* get_str);
static int32_t file_handle_get_integer_impl(ifile_handle_t* p_ifile_handle, int32_t int_type,
                                            int32_t* get_int);
static int32_t file_handle_get_buffer_impl(ifile_handle_t* p_ifile_handle, int32_t buff_type,
                                           uint8_t* get_buff, uint32_t* buff_size);

static int32_t check_file_handle(ifile_handle_t* p_ifile_handle) {
    file_module_return_t retval = FILE_MODULE_SUCCESS;
    if (NULL == p_ifile_handle) {
        log_error("Iterface of file handle is null!");
        retval = FILE_MODULE_IFACE_INVALID;
        goto EXIT;
    }

    file_data_t* file_data = (file_data_t*)p_ifile_handle->context;
    if (NULL == file_data) {
        log_error("Context in iterface of file handle is null!");
        retval = FILE_MODULE_CONTEXT_INVALID;
        goto EXIT;
    }

    if (NULL == file_data->fp) {
        log_error("Please make instance of file handle first!");
        retval = FILE_MODULE_INSTANCE_INVALID;
        goto EXIT;
    }
EXIT:
    return retval;
}

static int file_handle_set_impl(ifile_handle_t* p_ifile_handle) {
    file_module_return_t retval = FILE_MODULE_SUCCESS;

    p_ifile_handle->init = file_handle_init_impl;
    p_ifile_handle->uninit = file_handle_uninit_impl;
    p_ifile_handle->make_instance = file_handle_make_instance_impl;
    p_ifile_handle->get_base_version = file_handle_get_base_version_impl;
    p_ifile_handle->get_string = file_handle_get_string_impl;
    p_ifile_handle->get_integer = file_handle_get_integer_impl;
    p_ifile_handle->get_buffer = file_handle_get_buffer_impl;

    return retval;
}

static int32_t file_handle_init_impl(ifile_handle_t* p_ifile_handle) {
    file_module_return_t retval = FILE_MODULE_SUCCESS;

    if (NULL == p_ifile_handle) {
        log_error("Iterface of file handle is null!");
        retval = FILE_MODULE_IFACE_INVALID;
        goto EXIT;
    }

    if (NULL == p_ifile_handle->context) {
        p_ifile_handle->context = (file_data_t*)calloc(1, sizeof(file_data_t));
        if (NULL == p_ifile_handle->context) {
            log_error("Allocate file handle context fail");
            retval = FILE_MODULE_OUT_OF_MEMORY;
        }
    }

EXIT:
    return retval;
}

static int32_t file_handle_uninit_impl(ifile_handle_t* p_ifile_handle) {
    file_module_return_t retval = FILE_MODULE_SUCCESS;

    if (NULL == p_ifile_handle) {
        log_error("Iterface of file handle is null!");
        retval = FILE_MODULE_IFACE_INVALID;
        goto EXIT;
    }

    file_data_t* p_file_data = (file_data_t*)p_ifile_handle->context;
    if (NULL == p_file_data) {
        log_error("Context in iterface of file handle is null!");
        retval = FILE_MODULE_CONTEXT_INVALID;
        goto EXIT;
    }

    if (NULL != p_file_data->fp) {
        retval = fclose(p_file_data->fp);
        p_file_data->fp = NULL;
    }

    p_file_data->base_name = NULL;
    p_file_data->ext_name = NULL;
    FREE(p_file_data->contents_buffer.buffer);
    FREE(p_file_data->contents_string.buffer);

    memset(p_file_data, 0, sizeof(file_data_t));

EXIT:
    return retval;
}

static int32_t file_handle_make_instance_impl(ifile_handle_t* p_ifile_handle, char* file_path) {
    file_module_return_t retval = FILE_MODULE_SUCCESS;

    if (NULL == p_ifile_handle) {
        log_error("Iterface of file handle is null!");
        retval = FILE_MODULE_IFACE_INVALID;
        goto EXIT;
    }

    if (NULL == file_path || strlen(file_path) == 0) {
        log_error("Input file path is invalid");
        retval = FILE_MODULE_INCORRECT_PARAM;
        goto EXIT;
    }

    file_data_t* p_file_data = (file_data_t*)p_ifile_handle->context;
    if (NULL == p_file_data) {
        log_error("Context in iterface of file handle is null!");
        retval = FILE_MODULE_CONTEXT_INVALID;
        goto EXIT;
    }

    if (NULL != p_file_data->fp) {
        log_debug("Un-init existed file instance.");
        p_ifile_handle->uninit(p_ifile_handle);
    }

    p_file_data->fp = fopen(file_path, "rb");
    if (NULL == p_file_data->fp) {
        log_error("File: %s can't be open! errno = %d: %s.", file_path, errno, strerror(errno));
        retval = FILE_MODULE_MAKE_INSTANCE_FAIL;
        goto EXIT;
    }

    p_file_data->size = get_file_size(p_file_data->fp);
    p_file_data->base_name = get_file_base_name(file_path);
    p_file_data->ext_name = get_file_extension_name(file_path);
    p_file_data->contents_buffer.buffer =
        (unsigned char*)calloc(p_file_data->size, sizeof(unsigned char));

    if (NULL == p_file_data->contents_buffer.buffer) {
        log_error("Allocate contents buffer fail!");
        retval = FILE_MODULE_OUT_OF_MEMORY;
    }

    p_file_data->contents_string.buffer =
        (unsigned char*)calloc(p_file_data->size, sizeof(unsigned char));
    if (NULL == p_file_data->contents_string.buffer) {
        log_error("Allocate contents string fail!");
        retval = FILE_MODULE_OUT_OF_MEMORY;
    }

    if (FILE_MODULE_OUT_OF_MEMORY == retval) {
        p_ifile_handle->uninit(p_ifile_handle);
        goto EXIT;
    }

    size_t* p_buffer_len = &(p_file_data->contents_buffer.size);
    *p_buffer_len = p_file_data->size;
    rewind(p_file_data->fp);
    retval =
        read_file_to_buffer(p_file_data->fp, p_file_data->contents_buffer.buffer, p_buffer_len);
    if (FILE_MODULE_SUCCESS != retval) {
        retval = FILE_MODULE_MAKE_INSTANCE_FAIL;
        goto EXIT;
    }

    size_t* p_string_len = &(p_file_data->contents_string.size);
    *p_string_len = p_file_data->size;
    rewind(p_file_data->fp);
    retval =
        read_file_to_string(p_file_data->fp, p_file_data->contents_string.buffer, p_string_len);
    if (FILE_MODULE_SUCCESS != retval) {
        retval = FILE_MODULE_MAKE_INSTANCE_FAIL;
        goto EXIT;
    }

EXIT:
    return retval;
}

static int32_t file_handle_get_base_version_impl(ifile_handle_t* p_ifile_handle,
                                                 char* base_version) {
    int32_t retval = 0;
    size_t str_length = sizeof(FILE_HANDLE_BASE_VER);

    if (NULL != base_version) {
        strncpy(base_version, FILE_HANDLE_BASE_VER, (str_length + 1));
    }

    return retval;
}

static int32_t file_handle_get_integer_impl(ifile_handle_t* p_ifile_handle, int32_t int_type,
                                            int32_t* get_int) {
    file_module_return_t retval = FILE_MODULE_SUCCESS;

    retval = check_file_handle(p_ifile_handle);
    if (FILE_MODULE_SUCCESS != retval) {
        goto EXIT;
    }

    file_data_t* file_data = (file_data_t*)p_ifile_handle->context;

    switch (int_type) {
        case GET_INT_FILE_SIZE: {
            *get_int = (int32_t)file_data->size;
        } break;

        case GET_INT_FILE_CONTENTS_BUFFER_LEN: {
            *get_int = (int32_t)file_data->contents_buffer.size;
        } break;

        case GET_INT_FILE_CONTENTS_STR_LEN: {
            *get_int = (int32_t)file_data->contents_string.size;
        } break;

        default: {
            log_error("Unknown integer type!");
            retval = FILE_MODULE_INCORRECT_PARAM;
        } break;
    }

EXIT:
    return retval;
}

static int32_t file_handle_get_string_impl(ifile_handle_t* p_ifile_handle, int32_t str_type,
                                           char* get_str) {
    file_module_return_t retval = FILE_MODULE_SUCCESS;

    retval = check_file_handle(p_ifile_handle);
    if (FILE_MODULE_SUCCESS != retval) {
        goto EXIT;
    }

    file_data_t* file_data = (file_data_t*)p_ifile_handle->context;

    switch (str_type) {
        case GET_STR_BASE_NAME: {
            strncpy(get_str, file_data->base_name, (strlen(file_data->base_name) + 1));
        } break;

        case GET_STR_EXTENSION: {
            strncpy(get_str, file_data->ext_name, (strlen(file_data->ext_name) + 1));
        } break;

        default: {
            log_error("Unknow string type!");
            retval = FILE_MODULE_INCORRECT_PARAM;
        } break;
    }

EXIT:
    return retval;
}

static int32_t file_handle_get_buffer_impl(ifile_handle_t* p_ifile_handle, int32_t buff_type,
                                           uint8_t* get_buff, uint32_t* buff_size) {
    file_module_return_t retval = FILE_MODULE_SUCCESS;

    retval = check_file_handle(p_ifile_handle);
    if (FILE_MODULE_SUCCESS != retval) {
        goto EXIT;
    }

    file_data_t* file_data = (file_data_t*)p_ifile_handle->context;

    switch (buff_type) {
        case GET_BUFFER_CONTENTS: {
            unsigned char* contents_buffer = file_data->contents_buffer.buffer;
            size_t contents_buffer_size = file_data->contents_buffer.size;
            if (*buff_size < contents_buffer_size) {
                // TODO: realloc as exception handler.
                log_error("Not expect! dest buffer size = %d, src buffer size = %zd", *buff_size,
                          contents_buffer_size);
                *buff_size = (uint32_t)contents_buffer_size;
                retval = FILE_MODULE_INCORRECT_PARAM;
                break;
            }

            memcpy(get_buff, contents_buffer, contents_buffer_size);
            *buff_size = (uint32_t)contents_buffer_size;
        } break;

        case GET_BUFFER_CONTENTS_STRING: {
            unsigned char* contents_string = file_data->contents_string.buffer;
            size_t contents_string_size = file_data->contents_string.size;
            if (*buff_size < (contents_string_size + 1)) {
                // TODO: realloc as exception handler.
                log_error("Not expect! dest buffer size = %d, src string size = %zd", *buff_size,
                          (contents_string_size + 1));
                *buff_size = (uint32_t)contents_string_size + 1;
                retval = FILE_MODULE_INCORRECT_PARAM;
                break;
            }

            strncpy(get_buff, contents_string, (contents_string_size + 1));
            *buff_size = (uint32_t)contents_string_size;
        } break;

        default: {
            log_error("Unknow buffer type!");
            retval = FILE_MODULE_INCORRECT_PARAM;
        } break;
    }

EXIT:
    return retval;
}

ifile_handle_t* New_FILE_HANDLE(void) {
    // TODO: Reference counting in file module.
    ifile_handle_t* p_file_handle = (ifile_handle_t*)calloc(1, sizeof(ifile_handle_t));
    file_handle_set_impl(p_file_handle);
    p_file_handle->init(p_file_handle);

    return p_file_handle;
}

int32_t Delete_FILE_HANDLE(ifile_handle_t* p_ifile_handle) {
    // TODO: Reference counting in file module.
    int32_t retval = FILE_MODULE_SUCCESS;

    if (NULL == p_ifile_handle) {
        log_error("Iterface of file handle is null!");
        retval = FILE_MODULE_IFACE_INVALID;
        goto EXIT;
    }

    p_ifile_handle->uninit(p_ifile_handle);
    FREE(p_ifile_handle);

EXIT:
    return retval;
}
