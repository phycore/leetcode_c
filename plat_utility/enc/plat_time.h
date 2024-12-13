#ifndef _PLAT_TIME_H
#define _PLAT_TIME_H

#include <stdint.h>

// TODO: A header only log will be great!
#ifdef _DEBUG_VERSION
#define LOG_DEBUG(...) log_debug(__VA_ARGS__)
#else
#define LOG_DEBUG(...)
#endif

// clang-format off
#define TIME_MEASURE_INIT(name) \
    plat_init_time()

#define TIME_MEASURE_START(name) \
    plat_get_time()

#define TIME_MEASURE_STOP(name, elapsed_time)        \
    elapsed_time = (plat_get_time() - elapsed_time); \
    LOG_DEBUG("%s spent: %lld ms.", #name, elapsed_time)
// clang-format on

void plat_init_time();
int64_t plat_get_time(void);
void plat_sleep_time(uint64_t milli_seconds);

#endif  // _PLAT_TIME_H