#include "Array.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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