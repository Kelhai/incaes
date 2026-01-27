#include "incaes/aes.h"
#include "internal/cipher.h"
#include "internal/key_expansion.h"
#include <stdlib.h>

block aes_128(block in, byte* key) {
    const byte Nk = 4;
    const byte Nr = 10;

    word *w = key_expansion(key, Nk, Nr);
    if (!w) return NULL;
    
    block out = cipher(in, Nr, Nk, w);

    free(w);
    return out;
}

