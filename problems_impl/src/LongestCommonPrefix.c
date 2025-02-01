#include "LongestCommonPrefix.h"

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "log.h"

#define MAX_STR_LEN (size_t)200

char* longestCommonPrefix(char** strs, int strsSize) {
    char* compare_ch = (char*)calloc(strsSize, sizeof(char));
    size_t str_len = (MAX_STR_LEN + 1);
    char* CommonPrefix = (char*)calloc(str_len, sizeof(char));

    // get min string length
    size_t min_str_len = USHRT_MAX;
    for (int idx_of_strs = 0; idx_of_strs < strsSize; idx_of_strs++) {
        log_debug("%s, strs[%d] = %s", __func__, idx_of_strs, strs[idx_of_strs]);
        size_t str_len = strlen(strs[idx_of_strs]);
        if (str_len <= min_str_len) {
            min_str_len = str_len;
        }
    }
    min_str_len = (min_str_len == (USHRT_MAX)) ? (0) : (min_str_len);

    int common_ch_idx = 0;
    int is_common = 1;
    for (common_ch_idx = 0; common_ch_idx < min_str_len; common_ch_idx++) {
        // accqure char
        for (int idx_of_strs = 0; idx_of_strs < strsSize; idx_of_strs++) {
            compare_ch[idx_of_strs] = *(strs[idx_of_strs] + common_ch_idx);
        }

        // compare char
        size_t ch_idx = 0;
        while ((ch_idx < strsSize) && ((ch_idx + 1) < strsSize)) {
            if (compare_ch[ch_idx] != compare_ch[ch_idx + 1]) {
                is_common = 0;
                break;
            }
            ch_idx++;
        }

        if (is_common == 0) {
            break;
        }
    }
    common_ch_idx--;

    log_debug("%s, common_ch_idx: %d", __func__, common_ch_idx);
    if (common_ch_idx >= 0) {
        // common_ch_idx = 0 -> copy_len = 1; copy strs[0][0]
        // common_ch_idx = 1 -> copy_len = 2; copy strs[0][0], str[0][1]
        // ...
        size_t copy_len = (common_ch_idx + 1);
        strncpy(CommonPrefix, strs[0], copy_len);
    } else {
        // common_ch_idx = -1 -> there is no common char!
        strncpy(CommonPrefix, "", 1);
    }

    free(compare_ch);
    compare_ch = NULL;

    return CommonPrefix;
}