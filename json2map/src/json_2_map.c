#include "json_2_map.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "log.h"
#include "map_data.h"

#define FREE(ptr)          \
    do {                   \
        if (NULL != ptr) { \
            free(ptr);     \
        }                  \
        ptr = NULL;        \
    } while (0)

static int32_t check_json_2_map_handle(ijson_2_map_t* p_ijson_2_map);

static int32_t json_2_map_set_impl(ijson_2_map_t* p_ijson_2_map, const int32_t mode);

static int32_t json_2_map_init_impl(ijson_2_map_t* p_ijson_2_map);
static int32_t json_2_map_uninit_impl(ijson_2_map_t* p_ijson_2_map);

static int32_t json_2_map_filepath_make_instance_impl(ijson_2_map_t* p_ijson_2_map,
                                                      void* opaque_data, uint32_t data_size);
static int32_t json_2_map_strbuffer_make_instance_impl(ijson_2_map_t* p_ijson_2_map,
                                                       void* opaque_data, uint32_t data_size);

static int32_t json_2_map_get_base_version_impl(ijson_2_map_t* p_ijson_2_map, char* base_version);
static int32_t json_2_map_get_components_version(ijson_2_map_t* p_ijson_2_map,
                                                 int32_t component_type, char* lib_version);
static int32_t json_2_map_get_all_keys_impl(ijson_2_map_t* p_ijson_2_map, char* key,
                                            uint32_t key_length);

static int32_t json_2_map_get_int_impl(ijson_2_map_t* p_ijson_2_map, char* key,
                                       int32_t* get_integer);
static int32_t json_2_map_get_char_impl(ijson_2_map_t* p_ijson_2_map, char* key, char* get_char);
static int32_t json_2_map_get_string_impl(ijson_2_map_t* p_ijson_2_map, char* key, char* get_str);
static int32_t json_2_map_get_float_impl(ijson_2_map_t* p_ijson_2_map, char* key, float* get_float);
static int32_t json_2_map_get_double_impl(ijson_2_map_t* p_ijson_2_map, char* key,
                                          double* get_double);
static void* json_2_map_get_vector_int_impl(ijson_2_map_t* p_ijson_2_map, char* key);
static void* json_2_map_get_vector_str_impl(ijson_2_map_t* p_ijson_2_map, char* key);

static int32_t check_json_2_map_handle(ijson_2_map_t* p_ijson_2_map) {
    json_2_map_return_t retval = JSON_2_MAP_SUCCESS;

    if (NULL == p_ijson_2_map) {
        log_error("Interface of json2map is null!");
        retval = JSON_2_MAP_IFACE_INVALID;
        goto EXIT;
    }

    if (NULL == p_ijson_2_map->context) {
        log_error("Context in interface of json 2 map handle is null!");
        retval = JSON_2_MAP_DATA_INVALID;
        goto EXIT;
    }

EXIT:
    return retval;
}

static int32_t json_2_map_init_impl(ijson_2_map_t* p_ijson_2_map) {
    json_2_map_return_t retval = JSON_2_MAP_SUCCESS;

    if (NULL == p_ijson_2_map) {
        log_error("Interface of json2map is null!");
        retval = JSON_2_MAP_IFACE_INVALID;
        goto EXIT;
    }

    if (NULL == p_ijson_2_map->context) {
        p_ijson_2_map->context = create_map_data(0);
        if (NULL == p_ijson_2_map->context) {
            log_error("Allocate map out of memory!");
            retval = JSON_2_MAP_OUT_OF_MEMORY;
        }
    }

EXIT:
    return retval;
}

static int32_t json_2_map_uninit_impl(ijson_2_map_t* p_ijson_2_map) {
    json_2_map_return_t retval = JSON_2_MAP_SUCCESS;

    if (NULL == p_ijson_2_map) {
        log_error("Interface of json2map is null!");
        retval = JSON_2_MAP_IFACE_INVALID;
        goto EXIT;
    }

    void* context = p_ijson_2_map->context;
    if (NULL != context) {
        destroy_map_data(context);
    }

EXIT:
    return retval;
}

static int32_t json_2_map_filepath_make_instance_impl(ijson_2_map_t* p_ijson_2_map,
                                                      void* opaque_data, uint32_t buffer_size) {
    json_2_map_return_t retval = JSON_2_MAP_SUCCESS;

    retval = check_json_2_map_handle(p_ijson_2_map);
    if (JSON_2_MAP_SUCCESS != retval) {
        goto EXIT;
    }

EXIT:

    return retval;
}

static int32_t json_2_map_strbuffer_make_instance_impl(ijson_2_map_t* p_ijson_2_map,
                                                       void* opaque_data, uint32_t data_size) {
    json_2_map_return_t retval = JSON_2_MAP_SUCCESS;

    retval = check_json_2_map_handle(p_ijson_2_map);
    if (JSON_2_MAP_SUCCESS != retval) {
        goto EXIT;
    }

EXIT:
    return retval;
}

static int32_t json_2_map_get_base_version_impl(ijson_2_map_t* p_ijson_2_map, char* base_version) {
    return 0;
}

static int32_t json_2_map_get_components_version(ijson_2_map_t* p_ijson_2_map,
                                                 int32_t component_type, char* lib_version) {
    return 0;
}

static int32_t json_2_map_get_all_keys_impl(ijson_2_map_t* p_ijson_2_map, char* key,
                                            uint32_t key_length) {
    return 0;
}

static int32_t json_2_map_get_int_impl(ijson_2_map_t* p_ijson_2_map, char* key,
                                       int32_t* get_integer) {
    return 0;
}

static int32_t json_2_map_get_char_impl(ijson_2_map_t* p_ijson_2_map, char* key, char* get_char) {
    return 0;
}

static int32_t json_2_map_get_string_impl(ijson_2_map_t* p_ijson_2_map, char* key, char* get_str) {
    return 0;
}

static int32_t json_2_map_get_float_impl(ijson_2_map_t* p_ijson_2_map, char* key,
                                         float* get_float) {
    return 0;
}

static int32_t json_2_map_get_double_impl(ijson_2_map_t* p_ijson_2_map, char* key,
                                          double* get_double) {
    return 0;
}

static void* json_2_map_get_vector_int_impl(ijson_2_map_t* p_ijson_2_map, char* key) {
    return NULL;
}
static void* json_2_map_get_vector_str_impl(ijson_2_map_t* p_ijson_2_map, char* key) {
    return NULL;
}

static int32_t json_2_map_set_impl(ijson_2_map_t* p_ijson_2_map, const int32_t mode) {
    json_2_map_return_t retval = JSON_2_MAP_SUCCESS;

    p_ijson_2_map->init = json_2_map_init_impl;
    p_ijson_2_map->uninit = json_2_map_uninit_impl;
    p_ijson_2_map->get_base_version = json_2_map_get_base_version_impl;
    p_ijson_2_map->get_components_version = json_2_map_get_components_version;

    p_ijson_2_map->map_get_all_keys = json_2_map_get_all_keys_impl;
    p_ijson_2_map->map_get_int = json_2_map_get_int_impl;
    p_ijson_2_map->map_get_char = json_2_map_get_char_impl;
    p_ijson_2_map->map_get_string = json_2_map_get_string_impl;
    p_ijson_2_map->map_get_float = json_2_map_get_float_impl;
    p_ijson_2_map->map_get_double = json_2_map_get_double_impl;
    p_ijson_2_map->map_get_vector_int = json_2_map_get_vector_int_impl;
    p_ijson_2_map->map_get_vector_str = json_2_map_get_vector_str_impl;

    if (J2MAP_CREATE_MODE_FILE_PATH == mode) {
        p_ijson_2_map->make_instance = json_2_map_filepath_make_instance_impl;
    } else if (J2MAP_CREATE_MODE_STRING_BUFF == mode) {
        p_ijson_2_map->make_instance = json_2_map_strbuffer_make_instance_impl;
    } else {
        log_error("JSON to map, wrong create mode!");
        retval = JSON_2_MAP_MAKE_INSTANCE_FAIL;
    }

    return retval;
}

ijson_2_map_t* create_json2map_handle(void* context, json2map_create_mode_t mode) {
    ijson_2_map_t* p_ijson_2_map = (ijson_2_map_t*)calloc(1, sizeof(ijson_2_map_t));
    json_2_map_set_impl(p_ijson_2_map, mode);
    p_ijson_2_map->init(p_ijson_2_map);

    char* opaque_data = (char*)context;
    p_ijson_2_map->make_instance(p_ijson_2_map, context, (uint32_t)strlen(opaque_data));

    return p_ijson_2_map;
}

int32_t destroy_json2map_handle(ijson_2_map_t* p_ijson_2_map) {
    json_2_map_return_t retval = JSON_2_MAP_SUCCESS;

    if (NULL == p_ijson_2_map) {
        log_error("Interface of json2map is null!");
        retval = JSON_2_MAP_IFACE_INVALID;
        goto EXIT;
    }

    p_ijson_2_map->uninit(p_ijson_2_map);
    FREE(p_ijson_2_map);

EXIT:
    return retval;
}