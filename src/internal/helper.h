#ifndef AES_INTERNAL
#error "This header is internal and not part of the public API"
#endif

#ifndef HELPER_H_
#define HELPER_H_

#include "incaes/def.h"

smatrix alloc_smatrix(void);
void free_smatrix(smatrix* in);

block alloc_block(void);
void free_block(block in);

smatrix block_to_smatrix(block in);
block smatrix_to_block(smatrix in);

#endif

