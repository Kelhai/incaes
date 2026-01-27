#include "incaes/def.h"
#include "internal/cipher.h"
#include "internal/helper.h"
#include "internal/aes_table.h"
#include "internal/math.h"

#include <stdio.h>

/*
 *  AES-128:
 *      Nr = 10
 *      Nk = 4
 *  AES-192:
 *      Nr = 12
 *      Nk = 6
 *  AES-256:
 *      Nr = 14
 *      Nk = 8
 */
block cipher(block in, byte Nr, byte Nk, word* w) {
    smatrix state = block_to_smatrix(in);
    add_round_key(state, w, 0);

    int round;
    for (round = 1; round < Nr; round++) {
        sub_bytes(state);
        shift_rows(state);
        mix_columns(state);
        add_round_key(state, w, round);
    }
    sub_bytes(state);
    shift_rows(state);
    add_round_key(state, w, round);

    block out = smatrix_to_block(state);
    free_smatrix(&state);
    return out;
}

/*
 *  XORs input smatrix 's' with round key specified by 'w' and 'round'
 */
void add_round_key(smatrix s, word* w, const int round) {
    for (int c = 0; c < 4; c++) {
        word k = w[4*round + c];
        s[0][c] ^= (k >> 24) & 0xffu;
        s[1][c] ^= (k >> 16) & 0xffu;
        s[2][c] ^= (k >>  8) & 0xffu;
        s[3][c] ^= (k >>  0) & 0xffu;
    }
}

void sub_bytes(smatrix s) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            s[i][j] = sbox[s[i][j]];
        }
    }
}

void shift_rows(smatrix s) {
    byte tmp[4];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            tmp[j] = s[i][(j+i) % 4];
        }
        for (int j = 0; j < 4; j++) {
            s[i][j] = tmp[j];
        }
    }
}

void mix_columns(smatrix s) {
    for (int c = 0; c < 4; c++) {
        byte s0 = s[0][c];
        byte s1 = s[1][c];
        byte s2 = s[2][c];
        byte s3 = s[3][c];

        s[0][c] = mul2(s0) ^ mul3(s1) ^ s2 ^ s3;
        s[1][c] = s0 ^ mul2(s1) ^ mul3(s2) ^ s3;
        s[2][c] = s0 ^ s1 ^ mul2(s2) ^ mul3(s3);
        s[3][c] = mul3(s0) ^ s1 ^ s2 ^ mul2(s3);
    }
}

