#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "json_2_map.h"
#include "log.h"

int main(int argc, char* argv[]) {
    int retval = EXIT_SUCCESS;

    // Read file from command line.
    char* option = argv[1];
    char* file_path = argv[2];
    // char* file_path = "D:\\github\\leetcode_c\\bin\\Debug\\TwoSum_case_1.json";
    if (NULL == file_path) {
        log_error("There is no argv[2]! Please input again.");
        retval = EXIT_FAILURE;
        goto EXIT;
    }

    ijson_2_map_t* ijson_2_map =
        create_json2map_handle((void*)file_path, J2MAP_CREATE_MODE_FILE_PATH);
    destroy_json2map_handle(ijson_2_map);
EXIT:
    return retval;
}