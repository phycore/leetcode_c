#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cmd_invoke.h"
#include "json_2_map.h"
#include "log.h"

int main(int argc, char* argv[]) {
    int retval = EXIT_SUCCESS;

    // Read file from command line.
    char* option = argv[1];
    char* file_path = argv[2];
    // char* file_path = "D:\\github\\leetcode_c\\problems\\TwoSum_case_1.json";
    // char* file_path = "D:\\github\\leetcode_c\\problems\\parsing_test_case.json";
    if (NULL == file_path) {
        log_error("There is no argv[2]! Please input again.");
        retval = EXIT_FAILURE;
        goto EXIT;
    }

    ijson_2_map_t* ijson_2_map =
        create_json2map_handle((void*)file_path, J2MAP_CREATE_MODE_FILE_PATH);

    int32_t cmd_id = 0;
    input_data_t in_data = {0};
    output_data_t out_data = {0};

    in_data.data_size = sizeof(ijson_2_map_t);
    in_data.in_context = (void*)ijson_2_map;

    ijson_2_map->map_get_int(ijson_2_map, "problem_id", &cmd_id);
    retval = command_handler(cmd_id, &in_data, &out_data);

    destroy_json2map_handle(ijson_2_map);
EXIT:
    return retval;
}