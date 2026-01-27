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

static word rcon[16] = {
    0x01000000u, 0x02000000u, 0x04000000u, 0x08000000u,
    0x10000000u, 0x20000000u, 0x40000000u, 0x80000000u,
    0x1b000000u, 0x36000000u
};

word* key_expansion(byte* key, byte Nk, byte Nr);

#endif

