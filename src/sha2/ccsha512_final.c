//
//  ccsha512_ltc_compress.c
//  corecrypto
//
//  Created by Zormeister on 29/7/2025.
//

#include "ccsha2_ltc_internal.h"
#include <corecrypto/cc_priv.h>
#include <corecrypto/ccdigest.h>

/* I referenced ccdigest_final_64be for this. */
void ccsha512_final(const struct ccdigest_info *di, ccdigest_ctx_t ctx,
                    void *digest)
{
    unsigned char *dgst = digest;
    ccdigest_nbits(di, ctx) += ccdigest_num(di, ctx) * 8;
    ccdigest_data(di, ctx)[ccdigest_num(di, ctx)++] = 0x80;

    /* If we don't have at least 16 bytes (for the length) left we need to add
     a second block. */
    if (ccdigest_num(di, ctx) > di->block_size - 16) {
        while (ccdigest_num(di, ctx) < 64) {
            ccdigest_data(di, ctx)[ccdigest_num(di, ctx)++] = 0;
        }
        di->compress(ccdigest_state(di, ctx), 1, ccdigest_data(di, ctx));
        ccdigest_num(di, ctx) = 0;
    }

    /* pad upto block_size minus 16 with 0s */
    while (ccdigest_num(di, ctx) < di->block_size - 8) {
        ccdigest_data(di, ctx)[ccdigest_num(di, ctx)++] = 0;
    }

    CC_STORE64_BE(ccdigest_nbits(di, ctx), ccdigest_data(di, ctx) + di->block_size - 8);
    di->compress(ccdigest_state(di, ctx), 1, ccdigest_data(di, ctx));

    /* copy output */
    for (unsigned int i = 0; i < di->output_size / 8; i++) {
        CC_STORE64_BE(ccdigest_state_u64(di, ctx)[i], dgst + (4 * i));
    }
}