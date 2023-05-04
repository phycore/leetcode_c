#ifndef _JSON_COMMON_H
#define _JSON_COMMON_H

#include "json.h"
#include <stdint.h>

void JSON_print_type(void);
int32_t JSON_traverse_objects(struct json_object_s* json_object);

#endif // _JSON_COMMON_H