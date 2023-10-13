#ifndef _MAP_SETTING_HELPER
#define _MAP_SETTING_HELPER

#include <stdint.h>

#include "json.h"

typedef enum {
    MAP_SETTING_HELPER_SUCCESS,
    MAP_SETTING_HELPER_FAIL,
    MAP_SETTING_HELPER_CONTEXT_NULL,
    MAP_SETTING_HELPER_JSON_KEY_NULL,
    MAP_SETTING_HELPER_JSON_VALUE_NULL,
    MAP_SETTING_HELPER_NO_JSON_TYPE,
} map_setting_helper_return_t;

int32_t map_set_json_value(void* context, struct json_string_s* json_key,
                           struct json_value_s* json_value);

#endif  // _MAP_SETTING_HELPER