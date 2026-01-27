#include <stdlib.h>
#include "incaes/def.h"
#include "internal/key_expansion.h"
#include "internal/key_expansion.h"
#include "test.h"

int main(void) {
    byte key[16] = {0x2bu, 0x7eu, 0x15u, 0x16u, 0x28u, 0xaeu, 0xd2u, 0xa6u, 0xabu, 0xf7u, 0x15u, 0x88u, 0x09u, 0xcfu, 0x4fu, 0x3cu};
    word* exp = key_expansion(key, 4, 10);

    word schedule[4] = {0x2b7e1516u, 0x28aed2a6u, 0xabf71588u, 0x09cf4f3cu};

    for (int i = 0; i < 4; i++) {
        ASSERT_EQ(exp[i], schedule[i]);
    }

    free(exp);
    return 0;
}

