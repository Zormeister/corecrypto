//
//  ccaes_ltc_decrypt_mode.c
//  corecrypto
//
//  Created by Zormeister on 28/7/2025.
//

#include "ccaes_ltc_internal.h"
#include <corecrypto/cc_priv.h>
#include <corecrypto/ccaes.h>

/* weird that the symbol is named this, but you know. whatecer works i guess. */
static int ccaes_ecb_decrypt_init(const struct ccmode_ecb *ecb, ccecb_ctx *ctx, size_t key_nbytes, const void *key)
{
    ccaes_ltc_init(key, key_nbytes, 0, ctx);

    return CCERR_OK;
}

static int ccaes_ecb_decrypt(const ccecb_ctx *ctx, size_t nblocks, const void *in, void *out)
{
    while (nblocks--) {
        ccaes_ltc_ecb_decrypt(in, out, __DECONST(ccecb_ctx *, ctx));
        in += CCAES_BLOCK_SIZE;
        out += CCAES_BLOCK_SIZE;
    }

    return CCERR_OK;
}

const struct ccmode_ecb ccaes_ltc_ecb_decrypt_mode = {
    .size = sizeof(struct ltc_rijndael_key),
    .block_size = CCAES_BLOCK_SIZE,
    .init = ccaes_ecb_decrypt_init,
    .ecb = ccaes_ecb_decrypt,
};
