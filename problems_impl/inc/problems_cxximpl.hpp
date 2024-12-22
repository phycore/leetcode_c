#ifndef _PROBLEMS_IMPL_HPP
#define _PROBLEMS_IMPL_HPP

#ifdef __cplusplus
#include <string>
using namespace std;

class p3_Solution {
   private:
    string sub_string;

   public:
    int lengthOfLongestSubstring(string s);
    void show_longest_substring(void);
};
#else
typedef struct p3_Solution p3_Solution;
#endif  // __cplusplus

#ifdef __cplusplus
extern "C" {
#endif

#define DECLARE_SOLUTION(number)     \
    DECLARE_CREATE_SOLUTION(number); \
    DECLARE_DELETE_SOLUTION(number)

#define DECLARE_CREATE_SOLUTION(number) void* create_##number##_solution(void)

#define DECLARE_DELETE_SOLUTION(number) void delete_##number##_solution(number##_Solution* p_self)

DECLARE_SOLUTION(p3);
int run_p3_solution(p3_Solution* p_self, char* s);

#ifdef __cplusplus
}  // extern "C"
#endif

#endif  // _PROBLEMS_IMPL_HPP