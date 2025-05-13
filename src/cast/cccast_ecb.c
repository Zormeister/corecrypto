//
//  cccast_ecb.c
//  corecrypto
//
//  Created by Zormeister on 13/5/2025.
//

#include <corecrypto/cccast.h>
#include <corecrypto/ccmode_impl.h>
#include <corecrypto/cc_priv.h>
#include "cast_lcl.h"

int cccast_setup(const struct ccmode_ecb *ecb, ccecb_ctx *ctx, size_t key_len, const void *key) {
    CAST_set_key((CAST_KEY *)ctx, key_len, key);
    return CCERR_OK;
}

int cccast_ecb_encrypt(const ccecb_ctx *ctx, size_t nblocks, const void *in, void *out) {
    uint32_t d[2];
    const CAST_KEY *key = (const CAST_KEY *)ctx;

    const void *cur_in = in;
    void *cur_out = out;

    while (nblocks--) {
        CC_LOAD32_LE(d[0], cur_in);
        CC_LOAD32_LE(d[1], cur_in+4);
		CAST_encrypt(d,__DECONST(CAST_KEY *, key)); /* TODO: should i fix the violation of the const marker? */
		CC_STORE32_LE(d[0], cur_out);
		CC_STORE32_LE(d[1], cur_out+4);

		cur_in += CCCAST_BLOCK_SIZE;
		cur_out += CCCAST_BLOCK_SIZE;
    }

    return CCERR_OK;
}

int cccast_ecb_decrypt(const ccecb_ctx *ctx, size_t nblocks, const void *in, void *out) {
    uint32_t d[2];
    const CAST_KEY *key = (const CAST_KEY *)ctx;

    const void *cur_in = in;
    void *cur_out = out;

    while (nblocks--) {
        CC_LOAD32_LE(d[0], cur_in);
        CC_LOAD32_LE(d[1], cur_in+4);
		CAST_decrypt(d,__DECONST(CAST_KEY *, key)); /* TODO: should i fix the violation of the const marker? */
		CC_STORE32_LE(d[0], cur_out);
		CC_STORE32_LE(d[1], cur_out+4);

		cur_in += CCCAST_BLOCK_SIZE;
		cur_out += CCCAST_BLOCK_SIZE;
    }

    return CCERR_OK;
}

const struct ccmode_ecb cccast_eay_ecb_encrypt_mode = {
    .size = sizeof(CAST_KEY),
    .block_size = CCCAST_BLOCK_SIZE,
    .init = cccast_setup,
    .ecb = cccast_ecb_encrypt,
};

const struct ccmode_ecb cccast_eay_ecb_decrypt_mode = {
    .size = sizeof(CAST_KEY),
    .block_size = CCCAST_BLOCK_SIZE,
    .init = cccast_setup,
    .ecb = cccast_ecb_decrypt,
};
