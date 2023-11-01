#ifndef _DO_PROB_API
#define _DO_PROB_API

#include <stdint.h>
#include <stdio.h>

#define MAX_INT_ARR_SIZE (size_t)256

#define DECLARE_API(name)                                                            \
    int32_t name(void* context, char** in_list, size_t in_list_len, char** out_list, \
                 size_t out_list_len)

DECLARE_API(do_TwoSum);
DECLARE_API(do_AddTwoNumbers);

#endif  // _DO_PROB_API