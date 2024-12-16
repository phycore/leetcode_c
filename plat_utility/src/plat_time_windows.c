#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "plat_time.h"

// clang-forma off
#define ONE_2_ONE              (1)
#define ONE_2_MILLI       (1000LL)
#define ONE_2_MICRO    (1000000LL)
#define ONE_2_NANO  (1000000000LL)
// clang-format on

static LARGE_INTEGER g_frequency;
static int64_t g_precesion;

void plat_init_time(void) {
    QueryPerformanceFrequency(&g_frequency);
    g_precesion = ONE_2_MILLI;
}

int64_t plat_get_time(void) {
    LARGE_INTEGER ticks;

    if (!QueryPerformanceCounter(&ticks)) {
        return -1;
    }

    return (int64_t)((ticks.QuadPart * g_precesion) / g_frequency.QuadPart);
}

void plat_sleep_time(uint64_t milli_seconds) { Sleep((DWORD)milli_seconds); }