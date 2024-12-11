#include "do_problems_api.h"

#include <string.h>

#include "Array.h"
#include "Linked_List.h"
#include "json_2_map.h"
#include "log.h"
#include "sorting.h"
#include "vec.h"

#if defined (_WIN32)
#include <windows.h>
#define PATH_LEN MAX_PATH
#elif defined (__linux__)
#include <limits.h>
#define PATH_LEN PATH_MAX
#endif

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

    struct SinglyList* p_expect_list_ans = NewList();
    struct SinglyList* p_list1 = NewList();
    struct SinglyList* p_list2 = NewList();

    BEGIN_INPUT();
    for (size_t keys_idx = 0; keys_idx < in_list_len; keys_idx++) {
        if (0 == strcmp(in_list[keys_idx], "ans")) {
            ans_val = order->map_get_vector_int(order, in_list[keys_idx]);
            size_t ans_size = ans_val->length;
            for (size_t idx = 0; idx < ans_size; idx++) {
                int push_val = ans_val->data[idx];
                PushNode(p_expect_list_ans, push_val);
            }
            log_info("%s, Expect ans_node:", __func__);
            TraversePrintNodes(p_expect_list_ans);
        }

        if (0 == strcmp(in_list[keys_idx], "l1")) {
            l1_val = order->map_get_vector_int(order, in_list[keys_idx]);
            size_t l1_size = l1_val->length;
            for (size_t idx = 0; idx < l1_size; idx++) {
                int push_val = l1_val->data[idx];
                PushNode(p_list1, push_val);
            }
            log_info("%s, Input l1_node:", __func__);
            TraversePrintNodes(p_list1);
        }

        if (0 == strcmp(in_list[keys_idx], "l2")) {
            l2_val = order->map_get_vector_int(order, in_list[keys_idx]);
            size_t l2_size = l2_val->length;
            for (size_t idx = 0; idx < l2_size; idx++) {
                int push_val = l2_val->data[idx];
                PushNode(p_list2, push_val);
            }
            log_info("%s, Input l2_node:", __func__);
            TraversePrintNodes(p_list2);
        }
    }
    END_INPUT();

    struct ListNode* l1 = p_list1->p_Head;
    struct ListNode* l2 = p_list2->p_Head;
    struct SinglyList* p_output_ans_list = NewList();
    p_output_ans_list->p_Head = addTwoNumbers(l1, l2);
    p_output_ans_list->length = GetListLength(p_output_ans_list);

    BEGIN_OUTPUT();
    log_info("%s, Output ans_node:", __func__);
    TraversePrintNodes(p_output_ans_list);
    END_OUTPUT();

    DeleteList(p_expect_list_ans);
    DeleteList(p_list1);
    DeleteList(p_list2);
    DeleteList(p_output_ans_list);

    return 0;
}

int32_t do_LongestSubstringWithoutRepeating(void* context, char** in_list, size_t in_list_len,
                                            char** out_list, size_t out_list_len) {
    ijson_2_map_t* order = (ijson_2_map_t*)context;

    int32_t ans = 0;
    char ans_s[PATH_LEN] = {'\0'};
    char s[PATH_LEN] = {'\0'};
    BEGIN_INPUT();
    for (size_t keys_idx = 0; keys_idx < in_list_len; keys_idx++) {
        if (0 == strcmp(in_list[keys_idx], "ans")) {
            order->map_get_int(order, in_list[keys_idx], &ans);
            log_info("%s, ans = %d", __func__, ans);
        }

        if (0 == strcmp(in_list[keys_idx], "ans_s")) {
            order->map_get_string(order, in_list[keys_idx], ans_s);
            log_info("%s, ans_s: %s", __func__, ans_s);
        }

        if (0 == strcmp(in_list[keys_idx], "s")) {
            order->map_get_string(order, in_list[keys_idx], s);
            log_info("%s, s: %s", __func__, s);
        }
    }
    END_INPUT();

    size_t length_of_longest_substring = lengthOfLongestSubstring(s);

    BEGIN_OUTPUT();
    log_info("%s, length of longest substring = %zu", __func__, length_of_longest_substring);
    END_OUTPUT();

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