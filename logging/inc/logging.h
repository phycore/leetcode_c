#ifndef _LOGGING_H
#define _LOGGING_H

#include <stdio.h>

// clang-format off
#define log_debug(...) printf(__VA_ARGS__); printf("\n");
#define log_info(...) printf(__VA_ARGS__); printf("\n");
#define log_warn(...) printf(__VA_ARGS__); printf("\n");
#define log_error(...) printf(__VA_ARGS__); printf("\n");
// clang-format on

#endif  // _LOGGING_H