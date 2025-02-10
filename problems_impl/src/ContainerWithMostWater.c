#include "ContainerWithMostWater.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "log.h"

int maxArea(int* height, int heightSize) {
    int max_area = 0;

    int* p_start = height;
    int* p_end = (height + heightSize);

    for (int* p_left = p_start; p_left < p_end; p_left++) {
        for (int* p_right = (p_end - 1); p_right > p_left; p_right--) {
            int container_height = (*p_left < *p_right) ? (*p_left) : (*p_right);
            int container_width = (int)(p_right - p_left);
            int area = (container_width * container_height);

            log_debug("%s, height: %d, width: %d, area: %d", __func__, container_height,
                      container_width, area);

            if (area > max_area) {
                max_area = area;
            }
        }
    }

    log_debug("%s, max_area = %d", __func__, max_area);
    return max_area;
}