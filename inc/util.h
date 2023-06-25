#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

#define ERROR -1
#define CONTINUE 0

#define check_error(x) \
{ \
    int __val = (x); \
    if (__val < 0) \
    { \
        printf("%s[ERROR][%s] (%s:%s():%d): %s\n", RED, __TIME__, __FILE__, __func__, __LINE__, strerror(errno)); \
        exit(EXIT_FAILURE); \
    } \
}

#define debug_print(msg, ...) \
{ \
    printf("[DEBUG][%s] ", __TIME__); \
    printf(msg, ##__VA_ARGS__); \
}

#endif // UTIL_H
