#include "json_2_map.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "file_module.h"
#include "json_parsing_helper.h"
#include "log.h"
#include "map_data.h"
#include "vector_storing_helper.h"

#define PATH_LEN 260
#define FREE(ptr)          \
    do {                   \
        if (NULL != ptr) { \
            free(ptr);     \
        }                  \
        ptr = NULL;        \
    } while (0)

static struct json_value_s* g_json_root;

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
static int32_t json_2_map_get_all_keys_impl(ijson_2_map_t* p_ijson_2_map, char** keys_list,
                                            uint32_t* size_of_keys);

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

    if (NULL != g_json_root) {
        uninit_json_parsing(g_json_root);
        g_json_root = NULL;
    }

    void* context = p_ijson_2_map->context;
    if (NULL != context) {
        destroy_map_data(context);
        p_ijson_2_map->context = NULL;
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

    char* file_path = (char*)opaque_data;
    ifile_handle_t* p_ifile_handle = NULL;
    p_ifile_handle = create_file_handle(file_path, FILE_OP_MODE_TXT_READ);

    char base_name[PATH_LEN] = {'\0'};
    char extension_name[PATH_LEN] = {'\0'};
    p_ifile_handle->get_string(p_ifile_handle, GET_STR_BASE_NAME, base_name);
    p_ifile_handle->get_string(p_ifile_handle, GET_STR_EXTENSION, extension_name);

    if (strcmp(extension_name, ".json") != 0) {
        log_error("It's not json file.");
        retval = JSON_2_MAP_INCORRECT_PARAM;
        goto EXIT;
    }

    size_t json_str_length = 0;
    p_ifile_handle->get_integer(p_ifile_handle, GET_INT_FILE_CONTENTS_STR_LEN,
                                (uint32_t*)&json_str_length);
    json_str_length = (json_str_length + 1);

    // Allocate string buffer and get json file in string from file handle.
    unsigned char* json_file_in_string = NULL;
    json_file_in_string = (unsigned char*)calloc(json_str_length, sizeof(unsigned char));
    p_ifile_handle->get_buffer(p_ifile_handle, GET_BUFFER_CONTENTS_STRING,
                               (uint8_t*)json_file_in_string, (uint32_t*)&json_str_length);
    log_debug("json_file_in_string: %s", json_file_in_string);

    void* context = p_ijson_2_map->context;
    if (NULL == g_json_root) {
        // TODO: Adjust json_root and map_data lifetime.
        g_json_root = init_json_parsing(json_file_in_string, json_str_length);
    }

    json_parsing_save_map(context, g_json_root);

EXIT:
    retval = destroy_file_handle(p_ifile_handle);
    if (NULL != json_file_in_string) {
        free(json_file_in_string);
        json_file_in_string = NULL;
    }

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

static int32_t json_2_map_get_all_keys_impl(ijson_2_map_t* p_ijson_2_map, char** keys_list,
                                            uint32_t* size_of_keys) {
    json_2_map_return_t retval = JSON_2_MAP_SUCCESS;

    retval = check_json_2_map_handle(p_ijson_2_map);
    if (JSON_2_MAP_SUCCESS != retval) {
        goto EXIT;
    }

    void* map_data = p_ijson_2_map->context;
    retval = map_data_get_keys(map_data, keys_list, size_of_keys);
EXIT:
    return retval;
}

static int32_t json_2_map_get_int_impl(ijson_2_map_t* p_ijson_2_map, char* key,
                                       int32_t* get_integer) {
    json_2_map_return_t retval = JSON_2_MAP_SUCCESS;

    retval = check_json_2_map_handle(p_ijson_2_map);
    if (JSON_2_MAP_SUCCESS != retval) {
        goto EXIT;
    }

    void* map_data = p_ijson_2_map->context;
    retval = map_data_get_int(map_data, key, get_integer);

    if (MAP_DATA_SUCCESS == retval) {
        log_debug("%s, key = %s, get_integer = %d", __func__, key, *get_integer);
    } else if (MAP_DATA_NO_KEY == retval) {
        log_warn("%s, there is no key: %s", __func__, key);
    } else {
    }

EXIT:
    return retval;
}

static int32_t json_2_map_get_char_impl(ijson_2_map_t* p_ijson_2_map, char* key, char* get_char) {
    json_2_map_return_t retval = JSON_2_MAP_SUCCESS;

    retval = check_json_2_map_handle(p_ijson_2_map);
    if (JSON_2_MAP_SUCCESS != retval) {
        goto EXIT;
    }

    void* map_data = p_ijson_2_map->context;
    retval = map_data_get_char(map_data, key, get_char);
    if (MAP_DATA_SUCCESS == retval) {
        log_debug("%s, key = %s, get_char = %c", __func__, key, *get_char);
    } else if (MAP_DATA_NO_KEY == retval) {
        log_warn("%s, there is no key: %s", __func__, key);
    } else {
    }

EXIT:
    return retval;
}

static int32_t json_2_map_get_string_impl(ijson_2_map_t* p_ijson_2_map, char* key, char* get_str) {
    json_2_map_return_t retval = JSON_2_MAP_SUCCESS;

    retval = check_json_2_map_handle(p_ijson_2_map);
    if (JSON_2_MAP_SUCCESS != retval) {
        goto EXIT;
    }

    void* map_data = p_ijson_2_map->context;
    retval = map_data_get_str(map_data, key, get_str);
    if (MAP_DATA_SUCCESS == retval) {
        log_debug("%s, key = %s, get_string = %s", __func__, key, *get_str);
    } else if (MAP_DATA_NO_KEY == retval) {
        log_warn("%s, there is no key: %s", __func__, key);
    } else {
    }

EXIT:
    return retval;
}

static int32_t json_2_map_get_float_impl(ijson_2_map_t* p_ijson_2_map, char* key,
                                         float* get_float) {
    json_2_map_return_t retval = JSON_2_MAP_SUCCESS;

    retval = check_json_2_map_handle(p_ijson_2_map);
    if (JSON_2_MAP_SUCCESS != retval) {
        goto EXIT;
    }

    void* map_data = p_ijson_2_map->context;
    retval = map_data_get_float(map_data, key, get_float);
    if (MAP_DATA_SUCCESS == retval) {
        log_debug("%s, key = %s, get_float = %f", __func__, key, *get_float);
    } else if (MAP_DATA_NO_KEY == retval) {
        log_warn("%s, there is no key: %s", __func__, key);
    } else {
    }

EXIT:
    return retval;
}

static int32_t json_2_map_get_double_impl(ijson_2_map_t* p_ijson_2_map, char* key,
                                          double* get_double) {
    json_2_map_return_t retval = JSON_2_MAP_SUCCESS;

    retval = check_json_2_map_handle(p_ijson_2_map);
    if (JSON_2_MAP_SUCCESS != retval) {
        goto EXIT;
    }

    void* map_data = p_ijson_2_map->context;
    retval = map_data_get_double(map_data, key, get_double);
    if (MAP_DATA_SUCCESS == retval) {
        log_debug("%s, key = %s, get_double = %f", __func__, key, *get_double);
    } else if (MAP_DATA_NO_KEY == retval) {
        log_warn("%s, there is no key: %s", __func__, key);
    } else {
    }

EXIT:
    return retval;
}

static void* json_2_map_get_vector_int_impl(ijson_2_map_t* p_ijson_2_map, char* key) {
    json_2_map_return_t retval = check_json_2_map_handle(p_ijson_2_map);
    if (JSON_2_MAP_SUCCESS != retval) {
        return NULL;
    }

    void* map_data = p_ijson_2_map->context;
    void* vector_int = NULL;
    vector_int = map_data_get_void_pointer(map_data, key);

    if (NULL == vector_int) {
        log_warn("%s, there is no key: %s", __func__, key);
        return NULL;
    }

    return vector_int;
}
static void* json_2_map_get_vector_str_impl(ijson_2_map_t* p_ijson_2_map, char* key) {
    json_2_map_return_t retval = check_json_2_map_handle(p_ijson_2_map);
    if (JSON_2_MAP_SUCCESS != retval) {
        return NULL;
    }

    void* map_data = p_ijson_2_map->context;
    void* vector_str = NULL;
    vector_str = map_data_get_void_pointer(map_data, key);
    if (NULL == vector_str) {
        log_warn("%s, there is no key: %s", __func__, key);
        return NULL;
    }

    return vector_str;
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
    init_vector_storing();

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
    uninit_vector_storing();
    FREE(p_ijson_2_map);

EXIT:
    return retval;
}