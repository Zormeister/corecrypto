//
//  ccmode_factory_cbc.c
//  corecrypto
//
//  Created by Zormeister on 9/5/2025.
//

#include <corecrypto/cc.h>
#include <corecrypto/ccmode_factory.h>
#include <corecrypto/ccmode_impl.h>
#include <corecrypto/cc_priv.h>

/* These functions are essentially act as wrappers so every implementation doesn't need to repeat the same code. */

struct factory_cbc_context {
    struct ccmode_ecb *ecb; /* we need this so we can run the cipher */
    ccecb_ctx ctx; /* self-explanetory ngl. */
};

int ccmode_cbc_init(const struct ccmode_cbc *cbc, cccbc_ctx *ctx, size_t key_len, const void *key) {
    struct _ccmode_cbc_key *fctx = (struct _ccmode_cbc_key *)ctx;

    fctx->ecb = (struct ccmode_ecb *)cbc->custom; /* set the custom. */

    return fctx->ecb->init(fctx->ecb, (ccecb_ctx *)&fctx->u, key_len, key);
}

int ccmode_cbc_encrypt(const cccbc_ctx *ctx, cccbc_iv *iv, size_t nblocks, const void *in, void *out) {
    const struct _ccmode_cbc_key *fctx = (const struct _ccmode_cbc_key *)ctx; /* immediately get the factory context. */
    void *cur_iv = iv;
    const void *cur_in = in;
    void *cur_out = out;

    if (nblocks == 0) { return CCERR_OK; } /* honestly why would anyone pass in zero. */

    /* iterate. */
    while (nblocks--) {
        cc_xor(fctx->ecb->block_size, cur_out, cur_out, cur_iv);
        fctx->ecb->ecb((ccecb_ctx *)&fctx->u, 1, cur_out, out);

        cur_iv = cur_out; /* set cur_iv to our ciphertext from the last block */
        cur_in += fctx->ecb->block_size;
        cur_out += fctx->ecb->block_size;
    }

    return CCERR_OK;
}

void ccmode_factory_cbc_encrypt(struct ccmode_cbc *cbc, const struct ccmode_ecb *ecb) {
    /* construct a cbc mode from an ecb mode. */

    cbc->block_size = ecb->block_size; /* equal block sizes */
    cbc->custom = ecb; /* this is how we get the selected ecb mode to the context in init */
    cbc->size = (sizeof(struct _ccmode_cbc_key) - sizeof(ccecb_ctx)) + ecb->size; /* take into account that the context size could be different across */

    cbc->init = ccmode_cbc_init;
    cbc->cbc = ccmode_cbc_encrypt;
}
