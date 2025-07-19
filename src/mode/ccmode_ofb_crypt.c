//
//  ccmode_ofb_crypt.c
//  corecrypto
//
//  Created by Zormeister on 13/6/2025.
//

#include "ccmode_internal.h"
#include <corecrypto/cc_priv.h>

int ccmode_ofb_crypt(ccofb_ctx *ctx, size_t nbytes, const void *in, void *out)
{
    struct _ccmode_ofb_key *okey = (struct _ccmode_ofb_key *)ctx;
    const uint8_t *in_ptr        = in;
    uint8_t *out_ptr             = out;

    /* way more efficient than just cycling it by block. maybe i should do this for other impls. */
    while (nbytes--) {
        if (okey->pad_len == okey->ecb->block_size) {
            okey->ecb->ecb(CCMODE_OFB_KEY_ECB_CTX(okey), 1, CCMODE_OFB_KEY_IV(okey), CCMODE_OFB_KEY_IV(okey));
            okey->pad_len = 0;
        }

        *out_ptr++ = *in_ptr++ ^ CCMODE_OFB_KEY_IV(okey)[okey->pad_len];
        okey->pad_len++;
    }

    return CCERR_OK;
}
