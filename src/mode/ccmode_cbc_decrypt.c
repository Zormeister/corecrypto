//
//  ccmode_cbc_decrypt.c
//  corecrypto
//
//  Created by Zormeister on 13/6/2025.
//

#include "ccmode_internal.h"
#include "corecrypto/ccmode.h"

int ccmode_cbc_decrypt(const cccbc_ctx *ctx, cccbc_iv *iv, size_t nblocks, const void *in, void *out)
{
    const struct _ccmode_cbc_key *fctx = (const struct _ccmode_cbc_key *)ctx;
    void *cur_iv = iv->b;

    /* iterate. */
    while (nblocks--) {
        ccecb_update(fctx->ecb, CCMODE_CBC_KEY_ECB_CTX(fctx), 1, in, out);
        cc_xor(ccecb_block_size(fctx->ecb), out, in, cur_iv);

        cur_iv = out;
        in += ccecb_block_size(fctx->ecb);
        out += ccecb_block_size(fctx->ecb);
    }

    return CCERR_OK;
}
