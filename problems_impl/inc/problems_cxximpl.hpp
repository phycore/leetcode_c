#ifndef _PROBLEMS_IMPL_HPP
#define _PROBLEMS_IMPL_HPP

#ifdef __cplusplus
#include <string>
#include <vector>
using namespace std;

class p3_Solution {
   private:
    string sub_string;

   public:
    int lengthOfLongestSubstring(string s);
    void show_longest_substring(void);
};

class p48_Solution {
   private:
    void vector_to_rotate_matrix(vector<vector<int>>& dest_matrix, vector<int>& ans_vector);

   public:
    void rotate(vector<vector<int>>& matrix);
};
#else
typedef struct p3_Solution p3_Solution;
typedef struct p48_Solution p48_Solution;
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

DECLARE_SOLUTION(p48);
void run_p48_solution(p48_Solution* p_self, int** matrix, int matrixSize, int* matrixColSize);

#ifdef __cplusplus
}  // extern "C"
#endif

#endif  // _PROBLEMS_IMPL_HPP