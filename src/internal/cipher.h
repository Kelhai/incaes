#ifndef AES_INTERNAL
#error "This header is internal and not part of the public API"
#endif

#ifndef CIPHER_H_
#define CIPHER_H_

#include "incaes/def.h"

block cipher(block in, byte Nr, word* w);
block inv_cipher(block in, byte Nr, word* w);

void add_round_key(smatrix s, word* w, const int round);

void sub_bytes(smatrix s);
void inv_sub_bytes(smatrix s);

void shift_rows(smatrix s);
void inv_shift_rows(smatrix s);

void mix_columns(smatrix s);
void inv_mix_columns(smatrix s);

#endif

