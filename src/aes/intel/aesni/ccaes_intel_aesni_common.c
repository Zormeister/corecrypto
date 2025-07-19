//
//  ccaes_intel_aesni_common.c
//  corecrypto
//
//  Created by Zormeister on 4/5/2025.
//

#include <corecrypto/cc_config.h>

#if CCAES_INTEL_ASM

#include "ccaes_intel_aesni_internal.h"
#include <corecrypto/cc_error.h>
#include <corecrypto/ccaes.h>
#include <emmintrin.h>
#include <immintrin.h>
#include <wmmintrin.h>

/* this is pain */
int ccaes_intel_aesni_expand_key(struct ccaes_intel_aesni_ctx *ctx, size_t key_len, const void *key)
{
    if (key_len == CCAES_KEY_SIZE_128) {
        ctx->round_keys[0] = _mm_loadu_si128(key);
        return ccaes_intel_aesni128_gen_round_keys(ctx);
    } else if (key_len == CCAES_KEY_SIZE_192) {
        ctx->round_keys[0] = _mm_loadu_si128(key);                     /* Key block 1. (16 bytes) */
        ctx->round_keys[1] = _mm_loadu_si64(key + CCAES_KEY_SIZE_128); /* Key block 2. (8 bytes) */
        return ccaes_intel_aesni192_gen_round_keys(ctx);
    } else if (key_len == CCAES_KEY_SIZE_256) {
        ctx->round_keys[0] = _mm_loadu_si128(key);
        ctx->round_keys[1] = _mm_loadu_si128((key + CCAES_KEY_SIZE_128));
        return ccaes_intel_aesni256_gen_round_keys(ctx);
    }
    return CCERR_PARAMETER;
}

__m128i ccaes_intel_aesni_run_cipher_encrypt(struct ccaes_intel_aesni_ctx *ctx, __m128i state)
{
    __m128i cur = state;

    /* Key 0 round */
    cur = _mm_xor_si128(cur, ctx->round_keys[0]);

    /* Regular rounds. */
    for (int i = 1; i < ctx->nrounds; i++) {
        cur = _mm_aesenc_si128(cur, ctx->round_keys[i]);
    }

    cur = _mm_aesenclast_si128(cur, ctx->round_keys[ctx->nrounds]);

    return cur;
}

__m128i ccaes_intel_aesni_run_cipher_decrypt(struct ccaes_intel_aesni_ctx *ctx, __m128i state)
{
    __m128i cur = state;

    /* Last key goes first, either key 10, 12 or 14. */
    cur = _mm_xor_si128(cur, ctx->round_keys[ctx->nrounds]);

    /* Regular rounds. */
    for (int i = (ctx->nrounds - 1); i > 0; i--) {
        cur = _mm_aesdec_si128(cur, ctx->round_keys[i]);
    }

    cur = _mm_aesdeclast_si128(cur, ctx->round_keys[0]);

    return cur;
}

#endif
