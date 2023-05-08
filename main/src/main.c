#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "json_common.h"
#include "leetcode_problems.h"
#include "logging.h"

int main(int argc, char* argv[]) {
    int32_t retval = 0;
    int32_t free_retval = 0;

    char* json_in_string = NULL;
    size_t str_length = 0;
    for (int prob_idx = 0; prob_idx < NUMS_OF_PROBS; prob_idx++) {
        JSON_print_type();

        json_in_string = (char*)&problems[prob_idx][0];
        str_length = strlen(json_in_string);
        log_info("json_string = %s", json_in_string);

        struct json_value_s* json_root = JSON_create_root(json_in_string, str_length);
        if (NULL == json_root) {
            log_warn("json_parse problem %d is fail.", prob_idx);
            continue;
        }

        struct json_object_s* json_root_object = JSON_get_object(json_root);

        retval = JSON_traverse_objects(json_root_object);

        free_retval = JSON_free_root(json_root);
    }

    return retval;
}