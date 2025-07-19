//
//  ccmode_cbc_encrypt.c
//  corecrypto
//
//  Created by Zormeister on 8/7/2025.
//

#include "ccmode_internal.h"

int ccmode_cbc_encrypt(const cccbc_ctx *ctx, cccbc_iv *iv, size_t nblocks, const void *in, void *out)
{
    const struct _ccmode_cbc_key *fctx = (const struct _ccmode_cbc_key *)ctx; /* immediately get the factory context. */
    void *cur_iv                       = iv;
    const void *cur_in                 = in;
    void *cur_out                      = out;

    if (nblocks == 0) { return CCERR_OK; } /* honestly why would anyone pass in zero. */

    /* iterate. */
    while (nblocks--) {
        cc_xor(fctx->ecb->block_size, cur_out, cur_in, cur_iv);
        fctx->ecb->ecb(CCMODE_CBC_KEY_ECB_CTX(fctx), 1, cur_out, cur_out);

        cur_iv = cur_out; /* set cur_iv to our ciphertext from the last block */
        cur_in += fctx->ecb->block_size;
        cur_out += fctx->ecb->block_size;
    }

    return CCERR_OK;
}