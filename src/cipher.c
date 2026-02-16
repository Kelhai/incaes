#include "incaes/def.h"
#include "internal/cipher.h"
#include "internal/helper.h"
#include "internal/aes_table.h"
#include "internal/math.h"

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
block cipher(block in, byte Nr, word* w) {
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

block inv_cipher(block in, byte Nr, word* w) {
    smatrix state = block_to_smatrix(in);
    add_round_key(state, w, Nr);
    int round;
    for (round = Nr - 1; round > 0; round--) {
        inv_shift_rows(state);
        inv_sub_bytes(state);
        add_round_key(state, w, round);
        inv_mix_columns(state);
    }
    inv_shift_rows(state);
    inv_sub_bytes(state);
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
    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 4; c++) {
            s[r][c] = sbox[s[r][c]];
        }
    }
}

void inv_sub_bytes(smatrix s) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            s[i][j] = inv_sbox[s[i][j]];
        }
    }
}

void shift_rows(smatrix s) {
    byte tmp[4];
    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 4; c++) {
            tmp[c] = s[r][(c+r) % 4];
        }
        for (int c = 0; c < 4; c++) {
            s[r][c] = tmp[c];
        }
    }
}

static inline int mod(int a, int b) {
    int r = a % b;
    return r < 0 ? r + b : r;
}

void inv_shift_rows(smatrix s) {
    byte tmp[4];
    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 4; c++) {
            tmp[c] = s[r][mod(c-r, 4)];
        }
        for (int c = 0; c < 4; c++) {
            s[r][c] = tmp[c];
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

void inv_mix_columns(smatrix s) {
    for (int c = 0; c < 4; c++) {
        byte s0 = s[0][c];
        byte s1 = s[1][c];
        byte s2 = s[2][c];
        byte s3 = s[3][c];

        s[0][c] = mulE(s0) ^ mulB(s1) ^ mulD(s2) ^ mul9(s3);
        s[1][c] = mul9(s0) ^ mulE(s1) ^ mulB(s2) ^ mulD(s3);
        s[2][c] = mulD(s0) ^ mul9(s1) ^ mulE(s2) ^ mulB(s3);
        s[3][c] = mulB(s0) ^ mulD(s1) ^ mul9(s2) ^ mulE(s3);
    }
}
