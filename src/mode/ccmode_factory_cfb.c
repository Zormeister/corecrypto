//
//  ccmode_factory_cfb.c
//  corecrypto
//
//  Created by Zormeister on 31/5/2025.
//

#include <corecrypto/cc.h>
#include <corecrypto/cc_priv.h>
#include <corecrypto/ccmode_factory.h>

#define CCMODE_CFB_FEEDBACK(ctx) ctx->u
#define CCMODE_CFB_ECB_CTX(ctx) (ccecb_ctx *)ctx->u + ccn_sizeof_size(ctx->ecb->block_size)


/* UNDER CONSTRUCTION!!! */

int ccmode_cfb_init(const struct ccmode_cfb *cfb, cccfb_ctx *ctx, size_t rawkey_len, const void *rawkey,
                    const void *iv)
{
    struct _ccmode_cfb_key *ckey = (struct _ccmode_cfb_key *)ctx;
    ckey->ecb = (const struct ccmode_ecb *)cfb->custom;
    ckey->pad_len = ckey->ecb->block_size;
    cc_memcpy(CCMODE_CFB_FEEDBACK(ckey), iv, ckey->ecb->block_size);
    return CCERR_OK;
}

int ccmode_cfb_encrypt(cccfb_ctx *ctx, size_t nbytes, const void *in, void *out) {
    struct _ccmode_cfb_key *ckey = (struct _ccmode_cfb_key *)ctx;
    
    cc_abort("wip.");

    /* way more efficient than just cycling it by block. maybe i should do this for other impls. */
    for (size_t i = 0; i < nbytes; i++) {
        if (ckey->pad_len == ckey->ecb->block_size) {
            ckey->ecb->ecb(CCMODE_CFB_ECB_CTX(ckey), 1, CCMODE_CFB_FEEDBACK(ckey), CCMODE_CFB_FEEDBACK(ckey));
            ckey->pad_len = 0;
        }

        cc_xor(1, (out + i), CCMODE_CFB_FEEDBACK(ckey) + ckey->pad_len, (in + i));
        ckey->pad_len++;
    }

    return CCERR_OK;
}

int ccmode_cfb_decrypt(cccfb_ctx *ctx, size_t nbytes, const void *in, void *out);

