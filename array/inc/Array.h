#ifndef _ARRAY_H
#define _ARRAY_H

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* twoSum(int* nums, int numsSize, int target, int* returnSize);

#endif  // _ARRAY_H