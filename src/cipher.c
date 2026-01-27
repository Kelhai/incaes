#include "incaes/def.h"
#include "internal/cipher.h"
#include "internal/helper.h"

/*
 *  Preconditions:
 *      - in and key are byte arrays of length 16
 *  AES-128:
 *      Nr = 10
 *      Nk = 4
 */
block cipher(block in, byte Nr, byte Nk, word* w) {
    smatrix state = block_to_smatrix(in);
    // transformations here
    block out = smatrix_to_block(state);
    free_smatrix(&state);
    return out;
}

