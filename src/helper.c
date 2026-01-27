#include "incaes/helper.h"
#include <stdlib.h>

smatrix alloc_smatrix(void) {
    smatrix out = calloc(4, sizeof(*out));
    if (!out) {
        return NULL;
    }

    for (int i = 0; i < 4; i++) {
        out[i] = calloc(4, sizeof(byte));
        if (!out[i]) {
            for (int j = i-1; j >= 0; j--) {
                free(out[i]);
            }
            free(out);
            return NULL;
        }
    }
    return out;
}

void free_smatrix(smatrix* in) {
    for (int i = 0; i < 4; i++) {
        free((*in)[i]);
    }
    free(*in);
}

block alloc_block(void) {
    block out = calloc(16, sizeof(byte));
    return out;
}

void free_block(block in) {
    free(in);
}

// See: FIPS-197:3.4
smatrix block_to_smatrix(block in) {
    smatrix out = alloc_smatrix();
    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) {
            out[r][c] = in[r + 4 * c];
        }
    }
    return out;
}

// See: FIPS-197:3.4
block smatrix_to_block(smatrix in) {
    block out = alloc_block();
    for (int c = 0; c < 3; c++) {
        for (int r = 0; r < 3; r++) {
            out[r + 4 * c] = in[r][c];
        }
    }
    return out;
}

