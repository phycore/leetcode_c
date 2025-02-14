#ifndef _COMMANDS_H
#define _COMMANDS_H

#define LEETCODE_BASE 0
#define CMD_JSON_2_MAP_TEST LEETCODE_BASE
#define DATA_STRUCT_BASE 3000
#define ALG_BASE 4000

typedef enum {
    CMD_LEETCODE_BASE = LEETCODE_BASE,
    CMD_LEETCODE_TWO_SUM = 1,
    CMD_LEETCODE_ADD_TWO_NUMBERS = 2,
    CMD_LEETCODE_LONGEST_SUBSTRING_WITHOUT_REPEATING = 3,
    CMD_LEETCODE_LONGEST_COMMON_PREFIX = 14,
    CMD_LEETCODE_SEARCH_INSERT_POSITION = 35,
    CMD_LEETCODE_ROTATE_IMAGE = 48,
    CMD_LEETCODE_LENGTH_OF_LAST_WORD = 58,
    CMD_LEETCODE_MINIMUN_SIZE_SUBARRAY_SUM = 209,
    CMD_DATA_STRUCT_RESERVED = (DATA_STRUCT_BASE + 1),
    CMD_ALG_BUBBLE_SORT = (ALG_BASE + 1),
    CMD_ALG_SELECTION_SORT = (ALG_BASE + 2),
} commands_t;

#endif