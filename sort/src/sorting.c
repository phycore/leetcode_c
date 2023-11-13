#include "sorting.h"

#include <stdio.h>
#include <stdlib.h>

#include "log.h"
#include "sorting_utils.h"

int32_t bubble_sort(int32_t* p_array, size_t size) {
    if (NULL != p_array) {
        for (size_t round_index = 0; round_index < size; round_index++) {
            log_debug("%s, total_size = %d, round: %d", __func__, size, round_index);
            for (size_t j = 0; j < (size - round_index - 1); j++) {
                log_debug("Compare array[%d], [%d]", j, j + 1);
                if (p_array[j] > p_array[j + 1]) {
                    log_debug("befor swap: %d, %d", p_array[j], p_array[j + 1]);
                    swap(&p_array[j], &p_array[j + 1]);
                    log_debug("after swap: %d, %d", p_array[j], p_array[j + 1]);
                }
            }
        }
    }

    return 0;
}

int32_t selection_sort(int32_t* p_array, size_t size) {
    if (NULL != p_array) {
        int32_t min_val = 0x7FFFFFFF;
        size_t min_index = 0;

        for (size_t suppose_min_index = 0; suppose_min_index < size; suppose_min_index++) {
            log_debug("%s, total_size = %d, round: %d, suppose min_val: %d", __func__, size,
                      suppose_min_index, p_array[suppose_min_index]);
            min_val = p_array[suppose_min_index];
            min_index = suppose_min_index;
            for (size_t j = (suppose_min_index + 1); j < size; j++) {
                if (p_array[j] < min_val) {
                    min_val = p_array[j];
                    min_index = j;
                }
            }

            if (min_index > suppose_min_index) {
                log_debug("%s, find array[%d] = %d is smaller than %d.", __func__, min_index,
                          p_array[min_index], p_array[suppose_min_index]);
                swap(&p_array[suppose_min_index], &p_array[min_index]);
            }
        }
    }

    return 0;
}