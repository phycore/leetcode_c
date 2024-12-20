#include "problems_wrapper.h"

#include <problems_impl.hpp>

int lengthOfLongestSubstring(char* s) {
    p3_Solution* p_solution = create_p3_solution();
    int length = do_lengthOfLongestSubstring(p_solution, s);
    delete_p3_solution(p_solution);

    return length;
}