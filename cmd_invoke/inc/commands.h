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
    CMD_DATA_STRUCT_RESERVED = (DATA_STRUCT_BASE + 1),
    CMD_ALG_BUBBLE_SORT = (ALG_BASE + 1),
    CMD_ALG_SELECTION_SORT = (ALG_BASE + 2),
} commands_t;

#endif