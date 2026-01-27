#ifndef AES_INTERNAL
#error "This header is internal and not part of the public API"
#endif

#ifndef CIPHER_H_
#define CIPHER_H_

#include "incaes/def.h"

block cipher(block in, byte Nr, byte Nk, word* w);

#endif

