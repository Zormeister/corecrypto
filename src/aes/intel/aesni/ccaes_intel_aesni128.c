//
//  ccaes_intel_aesni128.c
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
#include <xmmintrin.h>

static __m128i expand(__m128i k1, __m128i k2)
{
    __m128i k = _mm_xor_si128(k1, _mm_slli_si128(k1, 4));
    k         = _mm_xor_si128(k, _mm_slli_si128(k, 4));
    k         = _mm_xor_si128(k, _mm_slli_si128(k, 4));
    k         = _mm_xor_si128(k, _mm_slli_si128(k, 4));

    return _mm_xor_si128(k, k2);
}

int ccaes_intel_aesni128_gen_round_keys(struct ccaes_intel_aesni_ctx *ctx)
{
    __m128i rk;

    rk                 = _mm_aeskeygenassist_si128(ctx->round_keys[0], 0x01);
    rk                 = _mm_shuffle_epi32(rk, 0xFF); /* Shuffle */
    ctx->round_keys[1] = expand(ctx->round_keys[0], rk);

    rk                 = _mm_aeskeygenassist_si128(ctx->round_keys[1], 0x02);
    rk                 = _mm_shuffle_epi32(rk, 0xFF); /* Shuffle */
    ctx->round_keys[2] = expand(ctx->round_keys[1], rk);

    rk                 = _mm_aeskeygenassist_si128(ctx->round_keys[2], 0x04);
    rk                 = _mm_shuffle_epi32(rk, 0xFF); /* Shuffle */
    ctx->round_keys[3] = expand(ctx->round_keys[2], rk);

    rk                 = _mm_aeskeygenassist_si128(ctx->round_keys[3], 0x08);
    rk                 = _mm_shuffle_epi32(rk, 0xFF); /* Shuffle */
    ctx->round_keys[4] = expand(ctx->round_keys[3], rk);

    rk                 = _mm_aeskeygenassist_si128(ctx->round_keys[4], 0x10);
    rk                 = _mm_shuffle_epi32(rk, 0xFF); /* Shuffle */
    ctx->round_keys[5] = expand(ctx->round_keys[4], rk);

    rk                 = _mm_aeskeygenassist_si128(ctx->round_keys[5], 0x20);
    rk                 = _mm_shuffle_epi32(rk, 0xFF); /* Shuffle */
    ctx->round_keys[6] = expand(ctx->round_keys[5], rk);

    rk                 = _mm_aeskeygenassist_si128(ctx->round_keys[6], 0x40);
    rk                 = _mm_shuffle_epi32(rk, 0xFF); /* Shuffle */
    ctx->round_keys[7] = expand(ctx->round_keys[6], rk);

    rk                 = _mm_aeskeygenassist_si128(ctx->round_keys[7], 0x80);
    rk                 = _mm_shuffle_epi32(rk, 0xFF); /* Shuffle */
    ctx->round_keys[8] = expand(ctx->round_keys[7], rk);

    rk                 = _mm_aeskeygenassist_si128(ctx->round_keys[8], 0x1B);
    rk                 = _mm_shuffle_epi32(rk, 0xFF); /* Shuffle */
    ctx->round_keys[9] = expand(ctx->round_keys[8], rk);

    rk                  = _mm_aeskeygenassist_si128(ctx->round_keys[9], 0x36);
    rk                  = _mm_shuffle_epi32(rk, 0xFF); /* Shuffle */
    ctx->round_keys[10] = expand(ctx->round_keys[9], rk);

    return CCERR_OK;
}

#endif
