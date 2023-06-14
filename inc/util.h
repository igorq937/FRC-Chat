#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define ERROR -1
#define CONTINUE 0


#define check_error(x) \
{ \
    int __val = (x); \
    if (__val < 0) \
    { \
        printf("[ERROR][%s] (%s:%s():%d): %s\n", __TIME__, __FILE__, __func__, __LINE__, strerror(errno)); \
        exit(EXIT_FAILURE); \
    } \
}

#define debug_print(msg, ...) \
{ \
    printf("[DEBUG][%s] ", __TIME__); \
    printf(msg, ##__VA_ARGS__); \
}

#endif // UTIL_H
