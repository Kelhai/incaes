#ifndef AES_H_
#define AES_H_

#include "def.h"

block aes_128(block in, byte* key);
block aes_192(block in, byte* key);
block aes_256(block in, byte* key);

#endif

