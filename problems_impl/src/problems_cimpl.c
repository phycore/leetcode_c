#include "problems_cimpl.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "log.h"

static void update_max(int* max, int* val);

static void update_max(int* max, int* val) {
    if (*val > *max) {
        *max = *val;
        log_debug("Update max value = %d", *max);
    }
}

int lengthOfLongestSubstring(char* s) {
    int max_length = (int)strlen(s);
    if (max_length <= 1) {
        return max_length;
    }

    char* sub_str = (char*)calloc((max_length + 1), sizeof(char));
    // clear max_length
    max_length = 0;

    int temp_length = 0;
    char* p_str = NULL;
    while ('\0' != *s) {
        // It have duplicated character!
        p_str = strchr(sub_str, *s);
        if (p_str) {
            temp_length = (int)strlen(sub_str);
            update_max(&max_length, &temp_length);

            // Remove duplicate character and before in sub_str!
            ++p_str;
            memmove(sub_str, p_str, strlen(p_str));
            memset((sub_str + strlen(p_str)), '\0', (strlen(sub_str) - strlen(p_str)));

            // String concatenate current character!
            strncat(sub_str, s, 1);
            log_debug("#2, After replace, sub_str = %s", sub_str);
        } else {
            // Searched characters are different!
            // String concatenate.
            strncat(sub_str, s, 1);
            temp_length = (int)strlen(sub_str);
            update_max(&max_length, &temp_length);

            log_debug("#1, After cat, sub_str = %s", sub_str);
        }

        s++;
    }

    if (NULL != sub_str) {
        free(sub_str);
        sub_str = NULL;
    }

    return max_length;
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