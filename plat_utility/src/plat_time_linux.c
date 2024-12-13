#include <stdio.h>
#include <time.h>
#include <unistd.h>

#include "plat_time.h"

// clang-format off
#define NANO_2_ONE (1000000000LL)
#define NANO_2_MILLI  (1000000LL)
#define NANO_2_MICRO     (1000LL)
#define NANO_2_NANO           (1)

#define ONE_2_ONE              (1)
#define ONE_2_MILLI       (1000LL)
#define ONE_2_MICRO    (1000000LL)
#define ONE_2_NANO  (1000000000LL)
// clang-format on

static int64_t g_precesion;

void plat_init_time(void) {
    g_precesion = NANO_2_MILLI;
}

int64_t plat_get_time(void) {
    struct timespec ticks;
    clock_gettime(CLOCK_MONOTONIC, &ticks);

    return (int64_t)((ticks.tv_sec * ONE_2_MILLI) + (ticks.tv_nsec/g_precesion));
}

void plat_sleep_time(uint64_t milli_seconds) {
    usleep((1000LL)*milli_seconds);
}