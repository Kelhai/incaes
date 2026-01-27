#ifndef AES_INTERNAL
#error "This header is internal and not part of the public API"
#endif

#ifndef CIPHER_H_
#define CIPHER_H_

#include "incaes/def.h"

block cipher(block in, byte Nr, byte Nk, word* w);
void add_round_key(smatrix s, word* w, const int round);
void sub_bytes(smatrix s);
void shift_rows(smatrix s);
void mix_columns(smatrix s);

#endif

