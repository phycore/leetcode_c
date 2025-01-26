#include <problems_cxximpl.hpp>

extern "C" {
#include "log.h"
}

void p3_Solution::show_longest_substring(void) {
    log_info("%s, string: %s", __func__, this->sub_string.c_str());
}

int p3_Solution::lengthOfLongestSubstring(string s) {
    string temp_string;
    size_t length = 0;
    size_t max_length = 0;

    for (auto it = s.begin(); it != s.end(); it++) {
        char ch = *it;

        size_t find_pos = temp_string.find_first_of(ch);
        if (string::npos == find_pos) {
            // char not exist.
            temp_string.push_back(ch);
            length = temp_string.length();
        } else {
            // char exist.
            temp_string = temp_string.substr((find_pos + 1), (length - 1));
            temp_string.push_back(ch);
        }

        if (length > max_length) {
            max_length = length;
            this->sub_string = temp_string;
        }

        log_debug("%s, longest length: %d", __func__, max_length);
    }

    this->show_longest_substring();
    return (int)max_length;
}

void* create_p3_solution(void) { return new p3_Solution; }

void delete_p3_solution(p3_Solution* p_self) { delete p_self; }

int run_p3_solution(p3_Solution* p_self, char* s) {
    string input_string(s);
    return p_self->lengthOfLongestSubstring(input_string);
}

void p48_Solution::rotate(vector<vector<int>>& matrix) {}

void* create_p48_solution(void) { return new p48_Solution; }

void delete_p48_solution(p48_Solution* p_self) { delete p_self; }

void run_p48_solution(p48_Solution* p_self, int** matrix, int matrixSize, int* matrixColSize) {}