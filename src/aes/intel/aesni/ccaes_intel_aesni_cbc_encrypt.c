//
//  ccaes_intel_aesni_cbc_encrypt.c
//  corecrypto
//
//  Created by Zormeister on 4/5/2025.
//

#include "ccaes_intel_aesni_internal.h"
#include <corecrypto/ccaes.h>
#include <corecrypto/ccmode_impl.h>

#if CCAES_INTEL_ASM

int ccaes_intel_aesni_cbc_encrypt_init(const struct ccmode_cbc *ecb, cccbc_ctx *ctx,
                                       size_t key_len, const void *key) {
    struct ccaes_intel_aesni_ctx *aesctx = (struct ccaes_intel_aesni_ctx *)ctx;

    if (key_len == CCAES_KEY_SIZE_128) {
        aesctx->nrounds = 10;
    } else if (key_len == CCAES_KEY_SIZE_192) {
        aesctx->nrounds = 12;
    } else if (key_len == CCAES_KEY_SIZE_256) {
        aesctx->nrounds = 14;
    }
    return ccaes_intel_aesni_expand_key(aesctx, key_len, key);
};

int ccaes_intel_aesni_cbc_encrypt_cbc(const cccbc_ctx *ctx, cccbc_iv *iv, size_t nblocks, const void *in, void *out) {
    struct ccaes_intel_aesni_ctx *aesctx = (struct ccaes_intel_aesni_ctx *)ctx;
    __m128i nextxor = _mm_loadu_si128((__m128i *)iv->b);

    while (nblocks--) {
        __m128i data = _mm_loadu_si128(in);
        data = _mm_xor_si128(data, nextxor); /* XOR the plaintext */
        data = ccaes_intel_aesni_run_cipher_encrypt(aesctx, data);
        nextxor = data;
        _mm_store_si128(out, data);
        in += CCAES_BLOCK_SIZE;
        out += CCAES_BLOCK_SIZE;
    }

    return CCERR_OK;
};

const struct ccmode_cbc ccaes_intel_cbc_encrypt_aesni_mode = {
    .size = ccn_sizeof_size(sizeof(struct ccaes_intel_aesni_ctx)),
    .block_size = CCAES_BLOCK_SIZE,
    .init = ccaes_intel_aesni_cbc_encrypt_init,
    .cbc = ccaes_intel_aesni_cbc_encrypt_cbc,
};

#endif
