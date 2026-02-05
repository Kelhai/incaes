#include "incaes/rijndael.h"
#include "internal/cipher.h"
#include "internal/key_expansion.h"
#include <stdlib.h>

static inline block aes_enc(block in, byte* key, const byte Nk, const byte Nr) {
    word *w = key_expansion(key, Nk, Nr);
    if (!w) return NULL;

    block out = cipher(in, Nr, w);

    free(w);
    return out;
}

static inline block aes_dec(block in, byte* key, const byte Nk, const byte Nr) {
    word *w = key_expansion(key, Nk, Nr);
    if (!w) return NULL;

    block out = inv_cipher(in, Nr, w);

    free(w);
    return out;
}

block aes_128_enc(block in, byte* key) {
    const byte Nk = 4;
    const byte Nr = 10;

    return aes_enc(in, key, Nk, Nr);
}

block aes_192_enc(block in, byte* key) {
    const byte Nk = 6;
    const byte Nr = 12;

    return aes_enc(in, key, Nk, Nr);
}

block aes_256_enc(block in, byte* key) {
    const byte Nk = 8;
    const byte Nr = 14;

    return aes_enc(in, key, Nk, Nr);
}

block aes_128_dec(block in, byte* key) {
    const byte Nk = 4;
    const byte Nr = 10;

    return aes_dec(in, key, Nk, Nr);
}

block aes_192_dec(block in, byte* key) {
    const byte Nk = 6;
    const byte Nr = 12;

    return aes_dec(in, key, Nk, Nr);
}

block aes_256_dec(block in, byte* key) {
    const byte Nk = 8;
    const byte Nr = 14;

    return aes_dec(in, key, Nk, Nr);
}
