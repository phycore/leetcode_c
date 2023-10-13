#ifndef _JSON_PARSING_HELPER_H
#define _JSON_PARSING_HELPER_H

#include <stdint.h>

#include "json.h"

typedef enum {
    JSON_PARSING_HELPER_SUCCESS,
    JSON_PARSING_HELPER_PARSING_FAIL,
    JSON_PARSING_HELPER_CONTEXT_NULL,
    JSON_PARSING_HELPER_ROOT_NULL,
} json_parsing_helper_return_t;

struct json_value_s* init_json_parsing(char* json_in_string, size_t str_length);
int32_t uninit_json_parsing(struct json_value_s* json_root);

int32_t json_parsing_save_map(void* context, struct json_value_s* json_root);
#endif  // _JSON_PARSING_HELPER_H