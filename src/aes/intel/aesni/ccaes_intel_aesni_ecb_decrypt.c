//
//  ccaes_intel_aesni_ecb.c
//  corecrypto
//
//  Created by Zormeister on 4/5/2025.
//

#include "ccaes_intel_aesni_internal.h"
#include <corecrypto/cc_error.h>
#include <corecrypto/ccaes.h>
#include <emmintrin.h>
#include <immintrin.h>
#include <wmmintrin.h>
#include <xmmintrin.h>

#if CCAES_INTEL_ASM

int ccaes_intel_aesni_ecb_decrypt_init(const struct ccmode_ecb *ecb, ccecb_ctx *ctx,
                                       size_t key_len, const void *key) {
    struct ccaes_intel_aesni_ctx *aesctx = (struct ccaes_intel_aesni_ctx *)ctx;

    if (key_len == CCAES_KEY_SIZE_128) {
        aesctx->nrounds = 10;
    } else if (key_len == CCAES_KEY_SIZE_192) {
        aesctx->nrounds = 12;
    } else if (key_len == CCAES_KEY_SIZE_256) {
        aesctx->nrounds = 14;
    }

    int res = ccaes_intel_aesni_expand_key(aesctx, key_len, key);

    for (int i = 0 ; i < aesctx->nrounds + 1; i++) {
        aesctx->round_keys[i] = _mm_aesimc_si128(aesctx->round_keys[i]);
    }

    return res;
};

int ccaes_intel_aesni_ecb_decrypt_ecb(const ccecb_ctx *ctx, size_t nblocks, const void *in, void *out) {
    struct ccaes_intel_aesni_ctx *aesctx = (struct ccaes_intel_aesni_ctx *)ctx;

    while (nblocks--) {
        __m128i data = _mm_loadu_si128(in);
        data = ccaes_intel_aesni_run_cipher_decrypt(aesctx, data);
        _mm_store_si128(out, data);
        in += CCAES_BLOCK_SIZE;
        out += CCAES_BLOCK_SIZE;
    }

    return CCERR_OK;
};

/* int (*init)(const struct ccmode_ecb *ecb, ccecb_ctx *ctx,
            size_t key_nbytes, const void *key);
int (*ecb)(const ccecb_ctx *ctx, size_t nblocks, const void *in,
           void *out); */

const struct ccmode_ecb ccaes_intel_ecb_decrypt_aesni_mode = {
    .size = ccn_sizeof_size(sizeof(struct ccaes_intel_aesni_ctx)),
    .block_size = CCAES_BLOCK_SIZE,
    .init = ccaes_intel_aesni_ecb_decrypt_init,
    .ecb = ccaes_intel_aesni_ecb_decrypt_ecb,
};

#endif
