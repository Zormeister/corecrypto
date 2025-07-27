//
//  ccmode_cbc_encrypt.c
//  corecrypto
//
//  Created by Zormeister on 8/7/2025.
//

#include "ccmode_internal.h"

int ccmode_cbc_encrypt(const cccbc_ctx *ctx, cccbc_iv *iv, size_t nblocks, const void *in, void *out)
{
    const struct _ccmode_cbc_key *fctx = (const struct _ccmode_cbc_key *)ctx;
    void *cur_iv = iv->b;

    /* iterate. */
    while (nblocks--) {
        cc_xor(ccecb_block_size(fctx->ecb), out, in, cur_iv);
        ccecb_update(fctx->ecb, CCMODE_CBC_KEY_ECB_CTX(fctx), 1, in, out);

        cur_iv = out;
        in += ccecb_block_size(fctx->ecb);
        out += ccecb_block_size(fctx->ecb);
    }

    return CCERR_OK;
}