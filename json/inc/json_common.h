#ifndef _JSON_COMMON_H
#define _JSON_COMMON_H

#include <stdint.h>

#include "json.h"

void JSON_print_type(void);
struct json_value_s* JSON_create_root(char* json_in_string, size_t str_length);
int32_t JSON_free_root(struct json_value_s* json_root);

struct json_object_s* JSON_get_object(struct json_value_s* json_node);
int32_t JSON_traverse_objects(struct json_object_s* json_object);

#endif  // _JSON_COMMON_H