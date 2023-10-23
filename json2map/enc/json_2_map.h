#ifndef _JSON_2_MAP_H
#define _JSON_2_MAP_H

#include <stdint.h>

#include "json_2_map_base.h"

typedef enum {
    J2MAP_CREATE_MODE_RESERVED = 0,
    J2MAP_CREATE_MODE_FILE_PATH,
    J2MAP_CREATE_MODE_STRING_BUFF,
} json2map_create_mode_t;

typedef enum {
    JSON_2_MAP_SUCCESS = 0,
    JSON_2_MAP_IFACE_INVALID,
    JSON_2_MAP_DATA_INVALID,
    JSON_2_MAP_MAKE_INSTANCE_FAIL,
    JSON_2_MAP_INSTANCE_INVALID,
    JSON_2_MAP_INCORRECT_PARAM,
    JSON_2_MAP_OUT_OF_MEMORY,
    JSON_2_MAP_FREE_DATA_FAIL,
} json_2_map_return_t;

typedef struct json_2_map {
    void* context;
    IJSON_2_MAP_MODULE_BASE(json_2_map);
} ijson_2_map_t;

ijson_2_map_t* create_json2map_handle(void* context, json2map_create_mode_t mode);
int32_t destroy_json2map_handle(ijson_2_map_t* p_ijson_2_map);

#endif  // _JSON_2_MAP_H