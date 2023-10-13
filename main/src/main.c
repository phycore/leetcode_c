#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

EXIT:
    return retval;
}