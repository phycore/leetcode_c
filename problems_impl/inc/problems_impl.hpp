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

void* create_p3_solution(void);
void delete_p3_solution(p3_Solution* p_self);
int do_lengthOfLongestSubstring(p3_Solution* p_self, char* s);

#ifdef __cplusplus
}  // extern "C"
#endif

#endif  // _PROBLEMS_IMPL_HPP