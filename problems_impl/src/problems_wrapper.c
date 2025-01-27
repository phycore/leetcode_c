#include "problems_wrapper.h"

#include <problems_cxximpl.hpp>

int lengthOfLongestSubstring_ex(char* s) {
    p3_Solution* p_solution = create_p3_solution();
    int length = run_p3_solution(p_solution, s);
    delete_p3_solution(p_solution);

    return length;
}

void rotateImage_ex(int** matrix, int matrixSize, int* matrixColSize) {
    p48_Solution* p_solution = create_p48_solution();
    run_p48_solution(p_solution, matrix, matrixSize, matrixColSize);
    delete_p48_solution(p_solution);
}