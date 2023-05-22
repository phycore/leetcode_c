#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "json_common.h"
#include "leetcode_problems.h"
#include "logging.h"

int main(int argc, char* argv[]) {
    int retval = 0;
    for (int32_t count_idx = 0; count_idx < argc; count_idx++) {
        log_debug("argv[%d] = %s", count_idx, argv[count_idx]);
    }

    unsigned char** pp_argument_vector = &argv[0];
    unsigned char* arg = *(pp_argument_vector + 1);
    unsigned char* p_file_name = *(pp_argument_vector + 2);
    unsigned char* json_file_in_string = NULL;
    uint32_t data_length = 0;
    FILE* fd = fopen(p_file_name, "rb");

    if (NULL == fd) {
        log_error("Open %s failed!", p_file_name);
    }

    if (NULL != fd) {
        fseek(fd, 0, SEEK_END);
        data_length = ftell(fd);
        fseek(fd, 0, SEEK_SET);
        size_t str_length = (data_length + 1);
        json_file_in_string = (unsigned char*)calloc(str_length, sizeof(unsigned char));

        int ch = 0;
        int idx = 0;
        while ((ch = fgetc(fd)) != EOF) {
            if ((isspace((unsigned char)ch)) || ((unsigned char)ch == '\n')) {
                continue;
            }
            *(json_file_in_string + idx) = (unsigned char)ch;
            idx++;
        }
        *(json_file_in_string + idx) = '\0';

        fclose(fd);

        size_t json_str_length = strlen(json_file_in_string);
        log_debug("json_file_in_string = %s", json_file_in_string);
        log_debug("json_str_length = %zd", json_str_length);

        JSON_print_type();

        struct json_value_s* json_root = JSON_create_root(json_file_in_string, json_str_length);
        if (NULL == json_root) {
            log_warn("json_parse fail.");
            return -1;
        }

        struct json_object_s* json_root_object = JSON_get_object(json_root);

        retval = JSON_traverse_objects(json_root_object);

        int free_retval = JSON_free_root(json_root);

        if (NULL != json_file_in_string) {
            free(json_file_in_string);
        }
    }
    return retval;
}