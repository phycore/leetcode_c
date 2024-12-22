#include "problems_wrapper.h"

#include <problems_cxximpl.hpp>

int lengthOfLongestSubstring_ex(char* s) {
    p3_Solution* p_solution = create_p3_solution();
    int length = run_p3_solution(p_solution, s);
    delete_p3_solution(p_solution);

    return length;
}