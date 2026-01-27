#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "incaes/def.h"
#include "incaes/key_expansion.h"
#include "incaes/key_expansion.h"

const byte vec[16] = {0x2bu, 0x7eu, 0x15u, 0x16u, 0x28u, 0xaeu, 0xd2u, 0xa6u, 0xabu, 0xf7u, 0x15u, 0x88u, 0x09u, 0xcfu, 0x4fu, 0x3cu,};

int main(void) {
    byte key[16];
    memcpy(key, vec, sizeof(key));

    word* exp = key_expansion(key, 4, 10);

    printf("%x %x %x %x\n", exp[0], exp[1], exp[2], exp[3]);

    free(key);
    free(exp);
    return 0;
}

