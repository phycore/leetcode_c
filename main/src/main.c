#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file_module.h"
#include "json_common.h"
#include "log.h"

#define PATH_LEN 260

int main(int argc, char* argv[]) {
    int retval = EXIT_SUCCESS;

    // Declare null pointer for interface of file handle and json file in string.
    ifile_handle_t* p_ifile_handle = NULL;
    unsigned char* json_file_in_string = NULL;

    // Read file from command line.
    char* option = argv[1];
    char* file_path = argv[2];
    // char* file_path = "D:\\github\\leetcode_c\\bin\\Debug\\TwoSum_case_1.json";
    if (NULL == file_path) {
        log_error("There is no argv[2]! Please input again.");
        retval = EXIT_FAILURE;
        goto EXIT;
    }

    // Create interface of file handle object.
    p_ifile_handle = create_file_handle(file_path, FILE_OP_MODE_TXT_READ);

    // log print file base name and extension name.
    char base_name[PATH_LEN] = {'\0'};
    char extension_name[PATH_LEN] = {'\0'};

    p_ifile_handle->get_string(p_ifile_handle, GET_STR_BASE_NAME, base_name);
    p_ifile_handle->get_string(p_ifile_handle, GET_STR_EXTENSION, extension_name);

    log_debug("File Handle process file base_name: %s", base_name);
    log_debug("File Handle process file extension_name: %s", extension_name);

    // Only process json files.
    if (strcmp(extension_name, ".json") != 0) {
        log_error("It's not json file.");
        goto EXIT;
    }

    JSON_print_type();

    // Query file handle how many string length need allocate.
    size_t json_str_length = 0;
    p_ifile_handle->get_integer(p_ifile_handle, GET_INT_FILE_CONTENTS_STR_LEN,
                                (uint32_t*)&json_str_length);
    json_str_length = (json_str_length + 1);

    // Allocate string buffer and get json file in string from file handle.
    json_file_in_string = (unsigned char*)calloc(json_str_length, sizeof(unsigned char));
    p_ifile_handle->get_buffer(p_ifile_handle, GET_BUFFER_CONTENTS_STRING,
                               (uint8_t*)json_file_in_string, (uint32_t*)&json_str_length);
    log_debug("json_file_in_string: %s", json_file_in_string);

    // Parsing json.
    struct json_value_s* json_root = JSON_create_root(json_file_in_string, json_str_length);
    if (NULL == json_root) {
        log_warn("json_parse fail.");
        retval = EXIT_FAILURE;
        goto EXIT;
    }

    struct json_object_s* json_root_object = JSON_get_object(json_root);

    // Traverse and print all objects.
    retval = JSON_traverse_objects(json_root_object);

    if (NULL != json_root) {
        int free_retval = JSON_free_root(json_root);
    }

    // TODO: json to map.
EXIT:
    destroy_file_handle(p_ifile_handle);
    if (NULL != json_file_in_string) {
        free(json_file_in_string);
    }

    return retval;
}