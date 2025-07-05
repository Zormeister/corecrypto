//
//  ccmode_cfb_decrypt.c
//  corecrypto
//
//  Created by Zormeister on 13/6/2025.
//

#include <corecrypto/cc_priv.h>
#include "ccmode_internal.h"

int ccmode_cfb_decrypt(cccfb_ctx *ctx, size_t nbytes, const void *in, void *out) {
    struct _ccmode_cfb_key *ckey = (struct _ccmode_cfb_key *)ctx;
    size_t block_size = ckey->ecb->block_size;
    const uint8_t *cur_in = in;
    uint8_t *cur_out = out;

    /* way more efficient than just cycling it by block. maybe i should do this for other impls. */
    while (nbytes--) {
        if (ckey->pad_len == block_size) {
            ckey->ecb->ecb(CCMODE_CFB_KEY_ECB_CTX(ckey), 1, CCMODE_CFB_KEY_PADDING(ckey), CCMODE_CFB_KEY_FEEDBACK(ckey));
            ckey->pad_len = 0;
        }

        CCMODE_CFB_KEY_PADDING(ckey)[ckey->pad_len] = *cur_in;
        *cur_out = *cur_in ^ CCMODE_CFB_KEY_FEEDBACK(ckey)[ckey->pad_len];
        ckey->pad_len++;
        cur_in++;
        cur_out++;
    }

    return CCERR_OK;
}
