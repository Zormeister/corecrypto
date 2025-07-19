//
//  ccmode_cfb8_init.c
//  corecrypto
//
//  Created by Zormeister on 14/6/2025.
//

#include "ccmode_internal.h"
#include <corecrypto/cc_priv.h>

int ccmode_cfb8_init(const struct ccmode_cfb8 *cfb, cccfb8_ctx *ctx, size_t rawkey_len, const void *rawkey,
                     const void *iv)
{
    struct _ccmode_cfb8_key *ckey = (struct _ccmode_cfb8_key *)ctx;
    ckey->ecb = (const struct ccmode_ecb *)cfb->custom;
    cc_memcpy(CCMODE_CFB8_KEY_FEEDBACK(ckey), iv, ckey->ecb->block_size);
    ckey->ecb->init(ckey->ecb, CCMODE_CFB8_KEY_ECB_CTX(ckey), rawkey_len, rawkey);
    ckey->ecb->ecb(CCMODE_CFB8_KEY_ECB_CTX(ckey), 1, CCMODE_CFB8_KEY_FEEDBACK(ckey), CCMODE_CFB8_KEY_PADDING(ckey));
    return CCERR_OK;
}
