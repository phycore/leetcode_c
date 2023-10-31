#include "cmd_invoke.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commands.h"
#include "do_problems_api.h"
#include "json_2_map.h"
#include "log.h"
#include "mem_utils.h"

#define MAX_SIZE_OF_KEYS (size_t)256
#define MAX_KEY_LEN (size_t)256

int32_t command_handler(uint32_t cmd_id, input_data_t* in_data, output_data_t* out_data) {
    cmd_invoke_return_t retval = CMD_INVOKE_OK;

    if (NULL == in_data || NULL == out_data) {
        log_error("%s, in_data or out_data is null!", __func__);
        retval = CMD_INVOKE_INCORRECT_PARAM;
        goto EXIT;
    }

    if (NULL == in_data->in_context || 0 == in_data->data_size) {
        log_error("%s, in_data is invalid!", __func__);
        retval = CMD_INVOKE_IN_DATA_INVALID;
        goto EXIT;
    }

    // TODO: Copy do problems api result(output_list) to out_data.

    log_info("%s, process problem cmd_id: %d", __func__, cmd_id);

    ijson_2_map_t* order = (ijson_2_map_t*)in_data->in_context;

    char** input_list = new_char_list(MAX_SIZE_OF_KEYS, MAX_KEY_LEN);
    uint32_t input_list_len = MAX_SIZE_OF_KEYS;
    order->map_get_all_keys(order, input_list, (uint32_t*)&input_list_len);

    char** output_list = new_char_list(MAX_SIZE_OF_KEYS, MAX_KEY_LEN);
    uint32_t output_list_len = MAX_SIZE_OF_KEYS;

    switch (cmd_id) {
        case CMD_LEETCODE_TWO_SUM: {
            retval = do_TwoSum(order, input_list, input_list_len, output_list, output_list_len);
            break;
        }

        case CMD_LEETCODE_ADD_TWO_NUMBERS: {
            retval =
                do_AddTwoNumbers(order, input_list, input_list_len, output_list, output_list_len);
            break;
        }

        case CMD_LEETCODE_LONGEST_SUBSTRING_WITHOUT_REPEATING: {
            break;
        }

        default: {
            break;
        }
    }

    delete_char_list(input_list, MAX_SIZE_OF_KEYS);
    delete_char_list(output_list, MAX_SIZE_OF_KEYS);

    log_info("%s, process problem cmd_id: %d and retval = %d", __func__, cmd_id, retval);
EXIT:
    return retval;
}