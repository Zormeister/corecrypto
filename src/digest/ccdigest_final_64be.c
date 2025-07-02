//
//  ccdigest_final_64be.c
//  corecrypto
//
//  Created by Zormeister on 2/7/25.
//

#include <corecrypto/ccdigest.h>
#include <corecrypto/ccdigest_priv.h>

/* Ripped from XNU, as per ccdigest_final_64le.c's license header */
void ccdigest_final_64be(const struct ccdigest_info *di, ccdigest_ctx_t ctx,
                          void *digest) {
    unsigned char *dgst = digest;
    ccdigest_nbits(di, ctx) += ccdigest_num(di, ctx) * 8;
    ccdigest_data(di, ctx)[ccdigest_num(di, ctx)++] = 0x80;
    
    /* If we don't have at least 8 bytes (for the length) left we need to add
     a second block. */
    if (ccdigest_num(di, ctx) > 64 - 8) {
        while (ccdigest_num(di, ctx) < 64) {
            ccdigest_data(di, ctx)[ccdigest_num(di, ctx)++] = 0;
        }
        di->compress(ccdigest_state(di, ctx), 1, ccdigest_data(di, ctx));
        ccdigest_num(di, ctx) = 0;
    }
    
    /* pad upto block_size minus 8 with 0s */
    while (ccdigest_num(di, ctx) < 64 - 8) {
        ccdigest_data(di, ctx)[ccdigest_num(di, ctx)++] = 0;
    }
    
    CC_STORE64_BE(ccdigest_nbits(di, ctx), ccdigest_data(di, ctx) + 64 - 8);
    di->compress(ccdigest_state(di, ctx), 1, ccdigest_data(di, ctx));
    
    /* copy output */
    for (unsigned int i = 0; i < di->output_size / 4; i++) {
        CC_STORE32_BE(ccdigest_state_u32(di, ctx)[i], dgst+(4*i));
    }
}
