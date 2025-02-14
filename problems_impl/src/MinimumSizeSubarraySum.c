#include "MinimumSizeSubarraySum.h"

#include <limits.h>
#include <stddef.h>

typedef struct side {
    int is_lock;
    int* p_position;
} side_t;

typedef struct window {
    int* p_start;
    int* p_end;
    side_t left;
    side_t right;
} window_t;

static void lock_side(side_t* p_side);
static void unlock_side(side_t* p_side);
static int get_lock(side_t* p_side);
static int get_area(window_t* p_window, side_t* p_side);
static int get_window_length(window_t* p_window);
static int update_min_len(int* min_len, window_t* p_window);
static int move_forward(window_t* p_window, side_t* p_side);

static void lock_side(side_t* p_side) { p_side->is_lock = 1; }

static void unlock_side(side_t* p_side) { p_side->is_lock = 0; }

static int get_lock(side_t* p_side) { return p_side->is_lock; }

static int get_area(window_t* p_window, side_t* p_side) {
    int area = 0;
    int* p_start = p_window->p_start;
    int* p_end = p_window->p_end;

    if (p_side->p_position >= p_start && p_side->p_position < p_end) {
        area = *(p_side->p_position);
    }

    return area;
}

static int get_window_length(window_t* p_window) {
    int* left_position = p_window->left.p_position;
    int* right_position = p_window->right.p_position;

    int length = ((int)(right_position - left_position) + 1);

    return length;
}

static int update_min_len(int* min_len, window_t* p_window) {
    int len = get_window_length(p_window);
    if (len < *min_len) {
        *min_len = len;
    }
    return *min_len;
}

static int move_forward(window_t* p_window, side_t* p_side) {
    int is_lock = get_lock(p_side);
    if (0 == is_lock) {
        int* p_boundary = p_window->p_end;
        int** pp_position = &(p_side->p_position);

        if (*pp_position < p_boundary) {
            (*pp_position)++;
        }
    }

    return 0;
}

int minSubArrayLen(int target, int* nums, int numsSize) {
    int min_len = INT_MAX;
    window_t min_window = {.p_start = nums,
                           .p_end = (nums + numsSize),
                           .left.p_position = nums,
                           .right.p_position = nums};
    window_t* p_window = &min_window;

    size_t add_area = 0;
    size_t minus_area = 0;

    lock_side(&(p_window->left));
    unlock_side(&(p_window->right));
    size_t area =
        (get_lock(&(p_window->right)) == 0) ? (get_area(p_window, &(p_window->right))) : (0);
    while (p_window->right.p_position < p_window->p_end) {
        while (area >= target) {
            unlock_side(&(p_window->left));
            update_min_len(&min_len, p_window);
            minus_area =
                (get_lock(&(p_window->left)) == 0) ? (get_area(p_window, &(p_window->left))) : (0);
            area -= minus_area;
            move_forward(p_window, &(p_window->left));
        }

        lock_side(&(p_window->left));
        unlock_side(&(p_window->right));
        move_forward(p_window, &(p_window->right));
        add_area =
            (get_lock(&(p_window->right)) == 0) ? (get_area(p_window, &(p_window->right))) : (0);
        area += add_area;

        if (area >= target) {
            update_min_len(&min_len, p_window);
            lock_side(&(p_window->right));
        }
    }
    min_len = (min_len == INT_MAX) ? (0) : (min_len);

    return min_len;
}