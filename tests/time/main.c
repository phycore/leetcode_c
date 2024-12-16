#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "plat_time.h"

int main(int argc, char* argv[]) {
    char* option = argv[1];
    char* str_time = argv[2];

    int64_t time_seconds = (str_time != NULL) ? (atoi(str_time)) : (0);
    int64_t milli_seconds = (1000LL) * time_seconds;

    plat_sleep_time(milli_seconds);

    return EXIT_SUCCESS;
}