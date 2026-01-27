#ifndef AES_INTERNAL
#error "This header is internal and not part of the public API"
#endif

#ifndef KEY_EXPANSION_
#define KEY_EXPANSION_

#include "incaes/def.h"
#include "aes_table.h"

static inline word rot_word(word in) {
    return (in << 8) | (in >> 24);
}

static inline word sub_word(word in) {
    return  (sbox[(in >> 24) & 0xFFu] << 24) |
            (sbox[(in >> 16) & 0xFFu] << 16) |
            (sbox[(in >>  8) & 0xFFu] <<  8) |
            (sbox[(in >>  0) & 0xFFu] <<  0);
}

static const word rcon[15] = {
    0x00000000,
    0x01000000,
    0x02000000,
    0x04000000,
    0x08000000,
    0x10000000,
    0x20000000,
    0x40000000,
    0x80000000,
    0x1b000000,
    0x36000000,
    0x6c000000,
    0xd8000000,
    0xab000000,
    0x4d000000
};

word* key_expansion(byte* key, byte Nk, byte Nr);

#endif

