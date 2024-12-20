#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cmd_invoke.h"
#include "json_2_map.h"
#include "log.h"
#include "plat_time.h"

#ifdef _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <stdlib.h>
#endif

int main(int argc, char* argv[]) {
#ifdef _CRTDBG_MAP_ALLOC
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
    int retval = EXIT_SUCCESS;

    // LOG_LEVEL was defined by CMakeLists.txt
    log_set_level(LOG_LEVEL);

    // Read file from command line.
    char* option = argv[1];
    char* file_path = argv[2];

    if (NULL == file_path) {
        log_error("There is no argv[2]! Please input again.");
        retval = EXIT_FAILURE;
        goto EXIT;
    }

    TIME_MEASURE_INIT(create_json2map_handle);
    int64_t time_json2map = TIME_MEASURE_START(create_json2map_handle);
    ijson_2_map_t* ijson_2_map =
        create_json2map_handle((void*)file_path, J2MAP_CREATE_MODE_FILE_PATH);
    TIME_MEASURE_STOP(create_json2map_handle, time_json2map);
    if (NULL == ijson_2_map) {
        log_error("Create json 2 map fail!");
        retval = EXIT_FAILURE;
        goto EXIT;
    }

    int32_t cmd_id = 0;
    input_data_t in_data = {0};
    output_data_t out_data = {0};

    in_data.data_size = sizeof(ijson_2_map_t);
    in_data.in_context = (void*)ijson_2_map;

    ijson_2_map->map_get_int(ijson_2_map, "problem_id", &cmd_id);
    TIME_MEASURE_INIT(command_handler);
    int64_t time_cmd = TIME_MEASURE_START(command_handler);
    retval = command_handler(cmd_id, &in_data, &out_data);
    TIME_MEASURE_STOP(command_handler, time_cmd);

    destroy_json2map_handle(ijson_2_map);
EXIT:

#ifdef _CRTDBG_MAP_ALLOC
    log_debug("%s, --Begin Memory Leak Detection--", __func__);
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
    _CrtCheckMemory();
    _CrtDumpMemoryLeaks();
    log_debug("%s, --End Memory Leak Detection--", __func__);
#endif

    return retval;
}