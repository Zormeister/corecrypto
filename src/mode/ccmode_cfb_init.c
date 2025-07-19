//
//  ccmode_cfb_init.c
//  corecrypto
//
//  Created by Zormeister on 13/6/2025.
//

#include "ccmode_internal.h"
#include <corecrypto/cc_priv.h>

int ccmode_cfb_init(const struct ccmode_cfb *cfb, cccfb_ctx *ctx, size_t rawkey_len, const void *rawkey,
                    const void *iv)
{
    struct _ccmode_cfb_key *ckey = (struct _ccmode_cfb_key *)ctx;
    ckey->ecb                    = (const struct ccmode_ecb *)cfb->custom;
    ckey->pad_len                = 0;
    cc_memcpy(CCMODE_CFB_KEY_FEEDBACK(ckey), iv, ckey->ecb->block_size);
    ckey->ecb->init(ckey->ecb, CCMODE_CFB_KEY_ECB_CTX(ckey), rawkey_len, rawkey);
    return CCERR_OK;
}
