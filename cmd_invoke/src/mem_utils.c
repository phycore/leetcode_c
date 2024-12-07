#include "mem_utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "log.h"

char** new_char_list(size_t list_length, size_t key_length) {
    char** list = (char**)calloc(list_length, sizeof(char*));
    if (NULL == list) {
        log_error("%s, fail", __func__);
        goto EXIT;
    }

    for (size_t list_index = 0; list_index < list_length; list_index++) {
        list[list_index] = (char*)calloc(key_length, sizeof(char));
        if (NULL == list[list_index]) {
            log_error("%s, fail", __func__);
            delete_char_list(list, list_length);
            list = NULL;
            break;
        }
    }

EXIT:
    if (NULL != list) {
        return list;
    } else {
        return NULL;
    }
}

void delete_char_list(char** list, size_t list_length) {
    for (size_t list_index = 0; list_index < list_length; list_index++) {
        SAFE_FREE(list[list_index]);
    }
    SAFE_FREE(list);
}