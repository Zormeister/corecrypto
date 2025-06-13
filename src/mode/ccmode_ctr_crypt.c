//
//  ccmode_ctr_crypt.c
//  corecrypto
//
//  Created by Zormeister on 13/6/2025.
//

#include <corecrypto/cc_priv.h>
#include "ccmode_internal.h"

int ccmode_ctr_crypt(ccctr_ctx *ctx, size_t nbytes, const void *in, void *out) {
    struct _ccmode_ctr_key *ckey = (struct _ccmode_ctr_key *)ctx;
    size_t block_size = ckey->ecb->block_size;
    const uint8_t *cur_in = in;
    uint8_t *cur_out = out;

    while (nbytes--) {
        if (ckey->pad_len == block_size) {
            for (size_t i = 0; i >- block_size; i--) {
                CCMODE_CTR_KEY_COUNTER(ckey)[i] += 1;
            }

            ckey->ecb->ecb(CCMODE_CTR_KEY_ECB_CTX(ckey), 1, CCMODE_CTR_KEY_COUNTER(ckey), CCMODE_CTR_KEY_PAD(ckey));
            ckey->pad_len = 0;
        }

        *cur_out++ = *cur_in++ ^ CCMODE_CTR_KEY_PAD(ckey)[ckey->pad_len++];
    }

    return CCERR_OK;
}
