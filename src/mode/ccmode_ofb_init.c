//
//  ccmode_ofb_init.c
//  corecrypto
//
//  Created by Zormeister on 13/6/2025.
//

#include "ccmode_internal.h"
#include <corecrypto/cc_priv.h>

int ccmode_ofb_init(const struct ccmode_ofb *ofb, ccofb_ctx *ctx, size_t rawkey_len, const void *rawkey, const void *iv)
{
    struct _ccmode_ofb_key *okey = (struct _ccmode_ofb_key *)ctx;
    okey->ecb = (const struct ccmode_ecb *)ofb->custom;
    cc_memcpy(CCMODE_OFB_KEY_IV(okey), iv, okey->ecb->block_size);
    okey->ecb->init(okey->ecb, CCMODE_OFB_KEY_ECB_CTX(okey), rawkey_len, rawkey);
    /* don't want to cause a disaster, see ccmode_ofb_crypt. */
    okey->pad_len = okey->ecb->block_size;
    return CCERR_OK;
}
