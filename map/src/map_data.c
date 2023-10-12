#include "map_data.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "log.h"
#include "map.h"

#define MAJOR_VER 0
#define MINOR_VER 0

#define IS_NULL(x, message, status) \
    do {                            \
        if (NULL == x) {            \
            log_error(message);     \
            return status;          \
        }                           \
    } while (0)

#define FREE(ptr)      \
    if (NULL != ptr) { \
        free(ptr);     \
    }                  \
    ptr = NULL

typedef struct map_desc {
    uint32_t ID;
    uint32_t major_version;
    uint32_t minor_version;
} map_desc_t;

typedef struct map_data {
    map_desc_t desc;
    map_void_t m_void;
    map_str_t m_str;
    map_int_t m_int;
    map_char_t m_char;
    map_float_t m_float;
    map_double_t m_double;
} map_data_t;

void* create_map_data(int ID) {
    size_t map_buffer_size = sizeof(map_data_t);
    uint8_t* map_buffer = (uint8_t*)malloc(map_buffer_size);
    map_data_t* map_data = (map_data_t*)map_buffer;

    // TODO: No duplicated ID!
    map_data->desc.ID = ID;
    map_data->desc.major_version = (uint32_t)MAJOR_VER;
    map_data->desc.minor_version = (uint32_t)MINOR_VER;
    log_info("map_data ID = %d; major_version = %d; minor_version = %d", map_data->desc.ID,
             map_data->desc.major_version, map_data->desc.minor_version);

    map_init(&(map_data->m_void));
    map_init(&(map_data->m_str));
    map_init(&(map_data->m_int));
    map_init(&(map_data->m_char));
    map_init(&(map_data->m_float));
    map_init(&(map_data->m_double));

    return map_data;
}

int destroy_map_data(void* context) {
    map_data_return_t retval = MAP_DATA_SUCCESS;

    IS_NULL(context, "Map context is null!", MAP_DATA_CONTEXT_NULL);

    map_data_t* map_data = (map_data_t*)context;

    map_deinit(&(map_data->m_void));
    map_deinit(&(map_data->m_str));
    map_deinit(&(map_data->m_int));
    map_deinit(&(map_data->m_char));
    map_deinit(&(map_data->m_float));
    map_deinit(&(map_data->m_double));

    FREE(map_data);
    return retval;
}

int map_data_set_void_pointer(void* context, char* key, void* value) {
    map_data_return_t retval = MAP_DATA_SUCCESS;

    IS_NULL(context, "Map context is null!", MAP_DATA_CONTEXT_NULL);
    IS_NULL(key, "Input key is null!", MAP_DATA_KEY_NULL);
    IS_NULL(value, "Input pointer to set void value is null!", MAP_DATA_VALUE_NULL);

    map_data_t* map_data = (map_data_t*)context;
    map_set(&(map_data->m_void), key, value);

    return retval;
}

void* map_data_get_void_pointer(void* context, char* key) {
    map_data_return_t retval = MAP_DATA_SUCCESS;

    IS_NULL(context, "Map context is null!", NULL);
    IS_NULL(key, "Input key is null!", NULL);

    map_data_t* map_data = (map_data_t*)context;
    return *(map_get(&(map_data->m_void), key));
}

int map_data_set_str(void* context, char* key, char* value) {
    map_data_return_t retval = MAP_DATA_SUCCESS;

    IS_NULL(context, "Map context is null!", MAP_DATA_CONTEXT_NULL);
    IS_NULL(key, "Input key is null!", MAP_DATA_KEY_NULL);
    IS_NULL(value, "Input pointer to set string(char*) value is null", MAP_DATA_VALUE_NULL);

    map_data_t* map_data = (map_data_t*)context;
    map_set(&(map_data->m_str), key, value);

    return retval;
}

int map_data_get_str(void* context, char* key, char* value) {
    map_data_return_t retval = MAP_DATA_SUCCESS;

    IS_NULL(context, "Map context is null!", MAP_DATA_CONTEXT_NULL);
    IS_NULL(key, "Input key is null!", MAP_DATA_KEY_NULL);
    IS_NULL(value, "Output pointer to get string(char*) value is null", MAP_DATA_VALUE_NULL);

    map_data_t* map_data = (map_data_t*)context;
    char** get_value = map_get(&(map_data->m_str), key);
    IS_NULL(get_value, "Key not exist!", MAP_DATA_NO_KEY);

    size_t str_length = strlen(*get_value);
    strncpy(value, *get_value, str_length);

    return retval;
}

int map_data_set_int(void* context, char* key, const int value) {
    map_data_return_t retval = MAP_DATA_SUCCESS;

    IS_NULL(context, "Map context is null!", EXIT_FAILURE);
    IS_NULL(key, "Input key is null!", EXIT_FAILURE);

    map_data_t* map_data = (map_data_t*)context;
    map_set(&(map_data->m_int), key, value);

    return retval;
}

int map_data_get_int(void* context, char* key, int* value) {
    map_data_return_t retval = MAP_DATA_SUCCESS;

    IS_NULL(context, "Map context is null!", MAP_DATA_CONTEXT_NULL);
    IS_NULL(key, "Input key is null!", MAP_DATA_KEY_NULL);
    IS_NULL(value, "Output pointer to get int value is null", MAP_DATA_VALUE_NULL);

    map_data_t* map_data = (map_data_t*)context;
    int* get_value = map_get(&(map_data->m_int), key);
    IS_NULL(get_value, "Key not exist!", MAP_DATA_NO_KEY);
    *value = *get_value;

    return retval;
}

int map_data_set_char(void* context, char* key, const char value) {
    map_data_return_t retval = MAP_DATA_SUCCESS;

    IS_NULL(context, "Map context is null!", MAP_DATA_CONTEXT_NULL);
    IS_NULL(key, "Input key is null!", MAP_DATA_KEY_NULL);

    // TODO: character-classification function

    map_data_t* map_data = (map_data_t*)context;
    map_set(&(map_data->m_char), key, value);

    return retval;
}

int map_data_get_char(void* context, char* key, char* value) {
    map_data_return_t retval = MAP_DATA_SUCCESS;

    IS_NULL(context, "Map context is null!", MAP_DATA_CONTEXT_NULL);
    IS_NULL(key, "Input key is null!", MAP_DATA_KEY_NULL);
    IS_NULL(value, "Output pointer to get char value is null", MAP_DATA_VALUE_NULL);

    map_data_t* map_data = (map_data_t*)context;
    char* get_value = map_get(&(map_data->m_char), key);
    IS_NULL(get_value, "Key not exist!", MAP_DATA_NO_KEY);
    *value = *get_value;

    return retval;
}

int map_data_set_float(void* context, char* key, const float value) {
    map_data_return_t retval = MAP_DATA_SUCCESS;

    IS_NULL(context, "Map context is null!", MAP_DATA_CONTEXT_NULL);
    IS_NULL(key, "Input key is null!", MAP_DATA_KEY_NULL);

    map_data_t* map_data = (map_data_t*)context;
    map_set(&(map_data->m_float), key, value);

    return retval;
}

int map_data_get_float(void* context, char* key, float* value) {
    map_data_return_t retval = MAP_DATA_SUCCESS;

    IS_NULL(context, "Map context is null!", MAP_DATA_CONTEXT_NULL);
    IS_NULL(key, "Input key is null!", MAP_DATA_KEY_NULL);
    IS_NULL(value, "Output pointer to get float value is null", MAP_DATA_VALUE_NULL);

    map_data_t* map_data = (map_data_t*)context;
    float* get_value = map_get(&(map_data->m_float), key);
    IS_NULL(get_value, "Key not exist!", MAP_DATA_NO_KEY);
    *value = *get_value;

    return retval;
}

int map_data_set_double(void* context, char* key, const double value) {
    map_data_return_t retval = MAP_DATA_SUCCESS;

    IS_NULL(context, "Map context is null!", MAP_DATA_CONTEXT_NULL);
    IS_NULL(key, "Input key is null!", MAP_DATA_KEY_NULL);

    map_data_t* map_data = (map_data_t*)context;
    map_set(&(map_data->m_double), key, value);

    return retval;
}

int map_data_get_double(void* context, char* key, double* value) {
    map_data_return_t retval = MAP_DATA_SUCCESS;

    IS_NULL(context, "Map context is null!", MAP_DATA_CONTEXT_NULL);
    IS_NULL(key, "Input key is null!", MAP_DATA_KEY_NULL);
    IS_NULL(value, "Output pointer to get double value is null", MAP_DATA_VALUE_NULL);

    map_data_t* map_data = (map_data_t*)context;
    double* get_value = map_get(&(map_data->m_double), key);
    IS_NULL(get_value, "Key not exist!", MAP_DATA_NO_KEY);
    *value = *get_value;

    return retval;
}

int map_data_remove_key(void* context, char* key) {
    map_data_return_t retval = MAP_DATA_SUCCESS;

    IS_NULL(context, "Map context is null!", MAP_DATA_CONTEXT_NULL);
    IS_NULL(key, "Input key is null!", MAP_DATA_KEY_NULL);

    map_data_t* map_data = (map_data_t*)context;
    map_remove(&(map_data->m_void), key);
    map_remove(&(map_data->m_str), key);
    map_remove(&(map_data->m_int), key);
    map_remove(&(map_data->m_char), key);
    map_remove(&(map_data->m_float), key);
    map_remove(&(map_data->m_double), key);

    return retval;
}
