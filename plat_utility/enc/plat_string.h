#ifndef _PLAT_STRING_H
#define _PLAT_STRING_H

#if defined(_WIN32)
#include <windows.h>
#define PATH_SEP '\\'
#define PATH_LEN MAX_PATH
#elif defined(__linux__)
#include <limits.h>
#define PATH_SEP '/'
#define PATH_LEN PATH_MAX
#endif

#endif