//
//  ccmode_cfb8_decrypt.c
//  corecrypto
//
//  Created by Zormeister on 14/6/2025.
//

#include "ccmode_internal.h"
#include <corecrypto/cc_priv.h>

int ccmode_cfb8_decrypt(cccfb8_ctx *ctx, size_t nbytes, const void *in, void *out)
{
    struct _ccmode_cfb8_key *ckey = (struct _ccmode_cfb8_key *)ctx;
    uint8_t *out_ptr = out;
    const uint8_t *in_ptr = in;

    while (nbytes--) {
        /* ZORMEISTER: this code is ugly but gets the job done */
        cc_memmove(CCMODE_CFB8_KEY_FEEDBACK(ckey), CCMODE_CFB8_KEY_FEEDBACK(ckey) + 1, (ckey->ecb->block_size - 1));
        CCMODE_CFB8_KEY_FEEDBACK(ckey)
        [(ckey->ecb->block_size - 1)] = *out_ptr = CCMODE_CFB8_KEY_PADDING(ckey)[0] ^ *in_ptr;
        ckey->ecb->ecb(CCMODE_CFB8_KEY_ECB_CTX(ckey), 1, CCMODE_CFB8_KEY_FEEDBACK(ckey), CCMODE_CFB8_KEY_PADDING(ckey));
        out_ptr++;
        in_ptr++;
    }

    return CCERR_OK;
}
