#ifndef HELPER_H_
#define HELPER_H_

#include "def.h"

smatrix alloc_smatrix(void);
void free_smatrix(smatrix* in);

block alloc_block(void);
void free_block(block in);

smatrix block_to_smatrix(block in);
block smatrix_to_block(smatrix in);

#endif

