#include "incaes/aes.h"
#include "incaes/def.h"
#include "internal/helper.h"
#include "internal/cipher.h"
#include "internal/aes_table.h"
#include "internal/key_expansion.h"
#include "test.h"
#include <stdlib.h>

void test_add_round_key() {
    smatrix state = alloc_smatrix();

    word w[4] = { 0x01020304, 0x05060708, 0x090a0b0c, 0x0d0e0f10 };
    add_round_key(state, w, 0);

    ASSERT_EQ(state[0][0], 0x01);
    ASSERT_EQ(state[1][0], 0x02);
    ASSERT_EQ(state[2][0], 0x03);
    ASSERT_EQ(state[3][0], 0x04);

    ASSERT_EQ(state[0][3], 0x0d);
    ASSERT_EQ(state[1][3], 0x0e);
    ASSERT_EQ(state[2][3], 0x0f);
    ASSERT_EQ(state[3][3], 0x10);

    free_smatrix(&state);
}

void test_sub_bytes() {
    smatrix s = alloc_smatrix();
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            s[i][j] = i * 4 + j;
        }
    }

    sub_bytes(s);

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            ASSERT_EQ(s[i][j], sbox[4*i + j]);
        }
    }
    free_smatrix(&s);
}

void test_shift_rows() {
    smatrix s = alloc_smatrix();

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            s[i][j] = i*4 + j;

    shift_rows(s);

    ASSERT(s[0][0] == 0);
    ASSERT(s[0][1] == 1);
    ASSERT(s[0][2] == 2);
    ASSERT(s[0][3] == 3);

    ASSERT(s[1][0] == 5);
    ASSERT(s[1][1] == 6);
    ASSERT(s[1][2] == 7);
    ASSERT(s[1][3] == 4);

    ASSERT(s[2][0] == 10);
    ASSERT(s[2][1] == 11);
    ASSERT(s[2][2] == 8);
    ASSERT(s[2][3] == 9);

    ASSERT(s[3][0] == 15);
    ASSERT(s[3][1] == 12);
    ASSERT(s[3][2] == 13);
    ASSERT(s[3][3] == 14);

    free_smatrix(&s);
}

void test_mix_columns() {
    smatrix s = alloc_smatrix();

    s[0][0] = 0xd4; s[1][0] = 0xbf; s[2][0] = 0x5d; s[3][0] = 0x30;

    mix_columns(s);

    ASSERT(s[0][0] == 0x04);
    ASSERT(s[1][0] == 0x66);
    ASSERT(s[2][0] == 0x81);
    ASSERT(s[3][0] == 0xe5);

    free_smatrix(&s);
}

void test_cipher_aes128() {
    byte plaintext[16] = { 0x32u, 0x43u, 0xf6u, 0xa8u, 0x88u, 0x5au, 0x30u, 0x8du, 0x31u, 0x31u, 0x98u, 0xa2u, 0xe0u, 0x37u, 0x07u, 0x34u };
    byte key[16] = { 0x2bu, 0x7eu, 0x15u, 0x16u, 0x28u, 0xaeu, 0xd2u, 0xa6u, 0xabu, 0xf7u, 0x15u, 0x88u, 0x09u, 0xcfu, 0x4fu, 0x3cu };

    word* w = key_expansion(key, 4, 10);

    byte expected_ciphertext[] = { 0x39u, 0x25u, 0x84u, 0x1du, 0x02u, 0xdcu, 0x09u, 0xfbu, 0xdcu, 0x11u, 0x85u, 0x97u, 0x19u, 0x6au, 0x0bu, 0x32u };

    block output = cipher(plaintext, 10, 4, w);

    for (int i = 0; i < 16; i++) {
        ASSERT_EQ(output[i], expected_ciphertext[i]);
    }

    free(output);
    free(w);
}


int main(void) {
    test_add_round_key();
    test_sub_bytes();
    test_shift_rows();
    test_mix_columns();
    test_cipher_aes128();
}
