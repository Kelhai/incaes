#include "internal/key_expansion.h"
#include <stdlib.h>

word* key_expansion(byte* key, byte Nk, byte Nr) {
    word* w = calloc(4 * (Nr + 1), sizeof(word));
    if (!w) return NULL;

    int i;
    for (i = 0; i < Nk; i++) {
        w[i] =  ((word) key[4*i + 0] << 24) |
                ((word) key[4*i + 1] << 16) |
                ((word) key[4*i + 2] <<  8) |
                ((word) key[4*i + 3] <<  0);
    }
    for (; i < 4*Nr + 4; i++) {
        word temp = w[i-1];

        if (i % Nk == 0) {
            temp = sub_word(rot_word(temp)) ^ rcon[i / Nk];
        } else if (Nk > 6 && i % Nk == 4) {
            temp = sub_word(temp);
        }
        w[i] = w[i - Nk] ^ temp;
    }
    return w;
}
