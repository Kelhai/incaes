#ifndef RIJNDAEL_H_
#define RIJNDAEL_H_

#include "def.h"

block aes_128_enc(block in, byte* key);
block aes_192_enc(block in, byte* key);
block aes_256_enc(block in, byte* key);

block aes_128_dec(block in, byte* key);
block aes_192_dec(block in, byte* key);
block aes_256_dec(block in, byte* key);

#endif

