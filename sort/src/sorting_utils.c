#include "sorting_utils.h"

#include <stdio.h>

void swap(int* left, int* right) {
    if (NULL != left && NULL != right) {
        int temp = *left;
        *left = *right;
        *right = temp;
    }
}