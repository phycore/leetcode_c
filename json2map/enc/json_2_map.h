#ifndef _JSON_2_MAP_H
#define _JSON_2_MAP_H

#include <stdint.h>

#include "json_2_map_base.h"

typedef struct json_2_map {
    void* context;
    IJSON_2_MAP_MODULE_BASE(json_2_map);
} ijson_2_map_t;

#endif  // _JSON_2_MAP_H