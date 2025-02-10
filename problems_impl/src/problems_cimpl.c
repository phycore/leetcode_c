#include "problems_cimpl.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "log.h"

int lengthOfLongestSubstring(char* s) {
    size_t length = strlen(s);
    char* p_sub_str = (char*)calloc((length + 1), sizeof(char));

    char* p_end = (s + length);
    size_t max_length = 0;

    size_t sub_idx = 0;
    for (char* p_ch = s; p_ch < p_end; p_ch++) {
        for (size_t idx = 0; idx < sub_idx; idx++) {
            if (p_sub_str[idx] == *p_ch) {
                size_t offset = (idx + 1);
                size_t move_len = (length + 1) - offset;
                memmove(p_sub_str, (p_sub_str + offset), move_len);
                sub_idx -= offset;
                break;
            }
        }
        p_sub_str[sub_idx] = *p_ch;
        size_t sub_length = strlen(p_sub_str);
        if (sub_length > max_length) {
            max_length = sub_length;
            log_debug("%s, %s", __func__, p_sub_str);
        }
        sub_idx++;
    }

    free(p_sub_str);
    p_sub_str = NULL;

    return (int)max_length;
}

int lengthOfLastWord(char* s) {
    log_debug("%s, s: %s, length of s = %d", __func__, s, strlen(s));

    int last_word_length = 0;
    char* p_cur_ch = (s + (strlen(s) - 1));
    while (p_cur_ch >= s) {
        if (isspace(*p_cur_ch)) {
            if (last_word_length > 0) {
                break;
            }
        } else {
            last_word_length++;
        }
        p_cur_ch--;
    }

    return last_word_length;
}