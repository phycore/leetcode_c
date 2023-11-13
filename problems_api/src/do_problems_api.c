#include "do_problems_api.h"

#include <string.h>

#include "Array.h"
#include "Linked_List.h"
#include "json_2_map.h"
#include "log.h"
#include "sorting.h"
#include "vec.h"

#define SORT_ALG_OFFSET 4000  // It's ALG_BASE in commands.h

#define BEGIN_INPUT()                         \
    do {                                      \
        log_info("Begin Input Information:"); \
    } while (0)

#define END_INPUT()                           \
    do {                                      \
        log_info("End Input Information:\n"); \
    } while (0)

#define BEGIN_OUTPUT()                         \
    do {                                       \
        log_info("Begin Output Information:"); \
    } while (0)

#define END_OUTPUT()                           \
    do {                                       \
        log_info("End Output Information:\n"); \
    } while (0)

static sort_fn g_sort_alg[] = {
    bubble_sort,
    selection_sort
};

int32_t do_TwoSum(void* context, char** in_list, size_t in_list_len, char** out_list,
                  size_t out_list_len) {
    ijson_2_map_t* order = (ijson_2_map_t*)context;

    int32_t target = 0;
    vec_int_t* nums_val = NULL;
    int nums[MAX_INT_ARR_SIZE] = {0};
    int numsSize = 0;
    int returnSize = 0;
    for (size_t keys_idx = 0; keys_idx < in_list_len; keys_idx++) {
        if (0 == strcmp(in_list[keys_idx], "target")) {
            order->map_get_int(order, in_list[keys_idx], &target);
        }

        if (0 == strcmp(in_list[keys_idx], "nums")) {
            nums_val = order->map_get_vector_int(order, in_list[keys_idx]);
            numsSize = nums_val->length;
            for (size_t idx = 0; idx < numsSize; idx++) {
                *(nums + idx) = nums_val->data[idx];
            }
        }
    }

    BEGIN_INPUT();
    for (size_t idx = 0; idx < numsSize; idx++) {
        log_info("%s, Input: nums[%d] = %d", __func__, idx, *(nums + idx));
    }
    log_info("%s, target = %d", __func__, target);
    END_INPUT();

    BEGIN_OUTPUT();
    int* index_array = twoSum(nums, numsSize, target, &returnSize);
    for (int idx = 0; idx < returnSize; idx++) {
        log_info("%s, Output: index_array[%d] = %d", __func__, idx, index_array[idx]);
    }
    END_OUTPUT();

    if (NULL != index_array) {
        free(index_array);
        index_array = NULL;
    }

    return 0;
}

int32_t do_AddTwoNumbers(void* context, char** in_list, size_t in_list_len, char** out_list,
                         size_t out_list_len) {
    ijson_2_map_t* order = (ijson_2_map_t*)context;

    vec_int_t* ans_val = NULL;
    vec_int_t* l1_val = NULL;
    vec_int_t* l2_val = NULL;

    struct ListNode ans = {0};
    struct ListNode l1 = {0};
    struct ListNode l2 = {0};
    for (size_t keys_idx = 0; keys_idx < in_list_len; keys_idx++) {
        if (0 == strcmp(in_list[keys_idx], "ans")) {
            ans_val = order->map_get_vector_int(order, in_list[keys_idx]);
            size_t ans_size = ans_val->length;
            for (size_t idx = 0; idx < ans_size; idx++) {
                // TODO: push node.
            }
        }

        if (0 == strcmp(in_list[keys_idx], "l1")) {
            l1_val = order->map_get_vector_int(order, in_list[keys_idx]);
            size_t l1_size = l1_val->length;
            for (size_t idx = 0; idx < l1_size; idx++) {
                // TODO: push node.
            }
        }

        if (0 == strcmp(in_list[keys_idx], "l2")) {
            l2_val = order->map_get_vector_int(order, in_list[keys_idx]);
            size_t l2_size = l2_val->length;
            for (size_t idx = 0; idx < l2_size; idx++) {
                // TODO: push node.
            }
        }
    }

    // struct ListNode* ans_node = addTwoNumbers(l1, l2);

    return 0;
}

int32_t do_sort(void* context, char** in_list, size_t in_list_len, char** out_list,
                size_t out_list_len) {
    ijson_2_map_t* order = (ijson_2_map_t*)context;

    int32_t problem_id = 0;
    vec_int_t* nums_val = NULL;
    int nums[MAX_INT_ARR_SIZE] = {0};
    int numsSize = 0;

    for (size_t keys_idx = 0; keys_idx < in_list_len; keys_idx++) {
        if (0 == strcmp(in_list[keys_idx], "problem_id")) {
            order->map_get_int(order, in_list[keys_idx], &problem_id);
        }

        if (0 == strcmp(in_list[keys_idx], "nums")) {
            nums_val = order->map_get_vector_int(order, in_list[keys_idx]);
            numsSize = nums_val->length;
            for (size_t idx = 0; idx < numsSize; idx++) {
                *(nums + idx) = nums_val->data[idx];
            }
        }
    }

    BEGIN_INPUT();
    for (size_t idx = 0; idx < numsSize; idx++) {
        log_info("%s, Input: nums[%d] = %d", __func__, idx, *(nums + idx));
    }
    END_INPUT();

    size_t sort_alg_index = ((size_t)problem_id - (size_t)SORT_ALG_OFFSET - (size_t)1);
    g_sort_alg[sort_alg_index](nums, numsSize);

    BEGIN_OUTPUT();
    for (int idx = 0; idx < numsSize; idx++) {
        log_info("%s, Output: nums[%d] = %d", __func__, idx, *(nums + idx));
    }
    END_OUTPUT();

    return 0;
}