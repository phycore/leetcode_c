#ifndef _CMD_INVOKE_H
#define _CMD_INVOKE_H

#include <stdint.h>
#include <stdio.h>

typedef enum {
    CMD_INVOKE_OK,
    CMD_INVOKE_INCORRECT_PARAM,
    CMD_INVOKE_IN_DATA_INVALID,
    CMD_INVOKE_OUT_DATA_INVALID,
    CMD_INVOKE_OUT_OF_MEMORY,
    CMD_INVOKE_WRONG_ANS,
} cmd_invoke_return_t;

typedef struct input_data {
    void* in_context;
    size_t data_size;
} input_data_t;

typedef struct output_data {
    void* out_context;
    size_t data_size;
} output_data_t;

int32_t command_handler(uint32_t cmd_id, input_data_t* in_data, output_data_t* out_data);

#endif  // _CMD_INVOKE_H