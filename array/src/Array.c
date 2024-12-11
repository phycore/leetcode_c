#include "Array.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "log.h"

static void update_max(int* max, int* val);

static void update_max(int* max, int* val) {
    if (*val > *max) {
        *max = *val;
        log_debug("Update max value = %d", *max);
    }
}

int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    *returnSize = 2;
    int arraySize = ((*returnSize) * sizeof(int));
    int* target_indexes = (int*)malloc(arraySize);
    memset(target_indexes, -1, arraySize);

    int sum_value = 0;
    for (int i = 0; i < numsSize; i++) {
        if (-1 != *(target_indexes)) {
            break;
        }
        sum_value = 0;
        for (int j = (i + 1); j < numsSize; j++) {
            sum_value = *(nums + i) + *(nums + j);
            if (sum_value == target) {
                *(target_indexes) = i;
                *(target_indexes + 1) = j;
                break;
            }
        }
    }

    return target_indexes;
}

int lengthOfLongestSubstring(char* s) {
    int max_length = (int)strlen(s);
    if (max_length <= 1) {
        return max_length;
    }

    char* sub_str = (char*)calloc((max_length + 1), sizeof(char));
    // clear max_length
    max_length = 0;

    int temp_length = 0;
    char* p_str = NULL;
    while ('\0' != *s) {
        // It have duplicated character!
        p_str = strchr(sub_str, *s);
        if (p_str) {
            temp_length = (int)strlen(sub_str);
            update_max(&max_length, &temp_length);

            // Remove duplicate character and before in sub_str!
            ++p_str;
            memmove(sub_str, p_str, strlen(p_str));
            memset((sub_str + strlen(p_str)), '\0', (strlen(sub_str) - strlen(p_str)));

            // String concatenate current character!
            strncat(sub_str, s, 1);
            log_debug("#2, After replace, sub_str = %s", sub_str);
        } else {
            // Searched characters are different!
            // String concatenate.
            strncat(sub_str, s, 1);
            temp_length = (int)strlen(sub_str);
            update_max(&max_length, &temp_length);

            log_debug("#1, After cat, sub_str = %s", sub_str);
        }

        s++;
    }

    if (NULL != sub_str) {
        free(sub_str);
        sub_str = NULL;
    }

    return max_length;
}