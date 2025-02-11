#include "SearchInsertPosition.h"

#include "log.h"

static int binary_search(int* nums, int numsSize, int target);
static int not_found_insert(int* nums, int numsSize, int target, int final_middle);

static int not_found_insert(int* nums, int numsSize, int target, int final_middle) {
    int target_index = -1;

    if ((final_middle - 1) >= 0 && (final_middle + 1) < numsSize) {
        // always insert and right shift.
        if (target < nums[final_middle] && target > nums[final_middle - 1]) {
            target_index = final_middle;
        } else if (target > nums[final_middle] && target < nums[final_middle + 1]) {
            target_index = (final_middle + 1);
        }
    } else {
        if (final_middle == 0) {
            if (target > nums[final_middle] && target < nums[final_middle + 1]) {
                target_index = (final_middle + 1);
            }
        } else if (final_middle == (numsSize - 1)) {
            if (target < nums[final_middle] && target > nums[final_middle - 1]) {
                target_index = final_middle;
            }
        } else {
            //
        }
    }

    return target_index;
}

static int binary_search(int* nums, int numsSize, int target) {
    int left = 0;
    int right = (numsSize - 1);
    int middle = 0;
    int target_index = -1;

    while (left <= right) {
        middle = ((left + right) >> 1);

        if (target < nums[middle]) {
            right = (middle - 1);
        } else if (target > nums[middle]) {
            left = (middle + 1);
        } else {
            target_index = middle;
            break;
        }
    }

    if (target_index == -1) {
        target_index = not_found_insert(nums, numsSize, target, middle);
    }

    return target_index;
}

int searchInsert(int* nums, int numsSize, int target) {
    int left = 0;
    int right = (numsSize - 1);
    int middle = 0;
    int insert = -1;

    if (target < nums[0]) {
        insert = 0;
    } else if (target > nums[right]) {
        insert = numsSize;
    } else {
        if (target == nums[0]) {
            insert = 0;
        } else if (target == nums[right]) {
            insert = right;
        } else {
            insert = binary_search(nums, numsSize, target);
        }
    }

    return insert;
}