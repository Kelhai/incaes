#ifndef AES_INTERNAL
#error "This header is internal and not part of the public API"
#endif

#ifndef MATH_H_
#define MATH_H_

#include "incaes/def.h"

static inline byte xtime(byte x) {
    return (x << 1) ^ ((x & 0x80u) ? 0x1bu : 0x00u);
}

static inline byte mul2(byte x) {
    return xtime(x);
}

static inline byte mul3(byte x) {
    return xtime(x) ^ x;
}

static inline byte mul9(byte x) {
    return xtime(xtime(xtime(x))) ^ x;
}

static inline byte mulB(byte x) {
    return xtime(xtime(xtime(x)) ^ x) ^ x;
}

static inline byte mulD(byte x) {
    return xtime(xtime(xtime(x) ^ x)) ^ x;
}

static inline byte mulE(byte x) {
    return xtime(xtime(xtime(x) ^ x) ^ x);
}

#endif

