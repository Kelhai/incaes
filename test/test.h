#ifndef AES_TEST_H_
#define AES_TEST_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define ASSERT(expr) \
    do { \
        if (!(expr)) { \
            fprintf(stderr, "ASSERTION FAILED: %s, %s:%d\n", #expr, __FILE__, __LINE__); \
            exit(1); \
        } \
    } while (0)

#define ASSERT_EQ(actual, expected) \
    do { \
        if ((actual) != (expected)) { \
            fprintf(stderr, "ASSERTION FAILED: %s == %s (%08x != %08x) at %s:%d\n", \
            #actual, #expected, (uint32_t)(actual), (uint32_t)(expected), __FILE__, __LINE__); \
            exit(1); \
        } \
    } while (0)

#endif

