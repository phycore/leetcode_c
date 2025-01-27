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

void p48_Solution::column_vector_to_matrix(vector<vector<int>>& dest_matrix,
                                           vector<vector<int>>& clm_vector) {
    size_t rows = dest_matrix.size();
    size_t clms = dest_matrix[0].size();
    size_t rows_of_clm_vector = clm_vector.size();

    size_t clm_vec_index = 0;
    if (rows_of_clm_vector == (rows * clms)) {
        for (size_t clm_index = 0; clm_index < clms; clm_index++) {
            for (size_t row_index = 0; row_index < rows; row_index++) {
                dest_matrix[row_index][clm_index] = clm_vector[clm_vec_index++][0];
            }
        }
    }
}

void p48_Solution::rotate(vector<vector<int>>& matrix) {
    if (matrix.empty()) {
        return;
    }

    size_t rows = matrix.size();
    size_t clms = matrix[0].size();

    // this->temp_matrix.clear();
    // this->temp_matrix.resize(rows, vector<int>(clms));
    vector<vector<int>> ans_clm_vec;
    for (int row_index = (rows - 1); row_index >= 0; row_index--) {
        // row vector
        vector<int> row_vec(matrix[row_index]);
        // column vector
        clms = matrix[row_index].size();
        vector<vector<int>> clm_vec(clms, vector<int>(1));
        for (size_t clm_index = 0; clm_index < clms; clm_index++) {
            clm_vec[clm_index][0] = row_vec[clm_index];
        }
        ans_clm_vec.insert(ans_clm_vec.end(), clm_vec.begin(), clm_vec.end());
    }

    // rewrite input matrix.
    this->column_vector_to_matrix(matrix, ans_clm_vec);
}

void* create_p48_solution(void) { return new p48_Solution; }

void delete_p48_solution(p48_Solution* p_self) { delete p_self; }

void run_p48_solution(p48_Solution* p_self, int** matrix, int matrixSize, int* matrixColSize) {
    int matrixRowSize = (matrixSize / (*matrixColSize));
    vector<vector<int>> input_matrix(matrixRowSize, vector<int>(*matrixColSize));
    // assigned input matrix
    for (size_t row_index = 0; row_index < matrixRowSize; row_index++) {
        for (size_t clm_index = 0; clm_index < *matrixColSize; clm_index++) {
            input_matrix[row_index][clm_index] = *(matrix[row_index] + clm_index);
        }
    }

    // rotate
    p_self->rotate(input_matrix);

    // rewrite matrix
    for (size_t row_index = 0; row_index < matrixRowSize; row_index++) {
        for (size_t clm_index = 0; clm_index < *matrixColSize; clm_index++) {
            *(matrix[row_index] + clm_index) = input_matrix[row_index][clm_index];
        }
    }
}