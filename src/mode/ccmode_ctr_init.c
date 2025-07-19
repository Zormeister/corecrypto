//
//  ccmode_ctr_setctr.c
//  corecrypto
//
//  Created by Zormeister on 13/6/2025.
//

#include "ccmode_internal.h"
#include <corecrypto/cc_priv.h>
#include <corecrypto/ccmode_factory.h>

int ccmode_ctr_init(const struct ccmode_ctr *ctr, ccctr_ctx *ctx, size_t rawkey_len, const void *rawkey, const void *iv)
{
    struct _ccmode_ctr_key *ckey = (struct _ccmode_ctr_key *)ctx;
    ckey->ecb                    = ctr->custom;
    ckey->ecb->init(ckey->ecb, CCMODE_CTR_KEY_ECB_CTX(ckey), rawkey_len, rawkey);
    ccmode_ctr_setctr(ctr, ctx, iv);
    return CCERR_OK;
}
