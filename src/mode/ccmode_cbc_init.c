//
//  ccmode_cbc_init.c
//  corecrypto
//
//  Created by Zormeister on 13/6/2025.
//

#include "ccmode_internal.h"
#include "corecrypto/ccmode.h"

int ccmode_cbc_init(const struct ccmode_cbc *cbc, cccbc_ctx *ctx, size_t key_len, const void *key)
{
    struct _ccmode_cbc_key *fctx = (struct _ccmode_cbc_key *)ctx;

    fctx->ecb = (struct ccmode_ecb *)cbc->custom; /* set the custom. */

    return ccecb_init(fctx->ecb, CCMODE_CBC_KEY_ECB_CTX(fctx), key_len, key);
}
