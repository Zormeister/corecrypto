//
//  ccaes_intel_aesni192.c
//  corecrypto
//
//  Created by Zormeister on 5/5/2025.
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

static void expand(__m128i *k1, __m128i *k2, __m128i *k3)
{
    __m128i k;

    *k2 = _mm_shuffle_epi32(*k2, 0x55);
    k   = _mm_slli_epi32(*k1, 0x4);
    *k1 = _mm_xor_si128(*k1, k);
    k   = _mm_slli_epi32(k, 0x4);
    *k1 = _mm_xor_si128(*k1, k);
    *k1 = _mm_xor_si128(*k1, *k2);
    *k2 = _mm_shuffle_epi32(*k1, 0xFF);
    k   = _mm_slli_epi32(*k3, 0x4);
    *k3 = _mm_xor_si128(*k3, k);
    *k3 = _mm_xor_si128(*k3, *k2);
}

int ccaes_intel_aesni192_gen_round_keys(struct ccaes_intel_aesni_ctx *ctx)
{
    /* who let the RK800 in here */
    __m128i rk0, rk1, rk2, rk3;
    /* Keys 0 and 1 are already loaded for us. we just need to work with the data. */

    /* Key 2 needs to be updated. */
    rk0 = ctx->round_keys[0];
    rk2 = ctx->round_keys[1];

    rk1 = _mm_aeskeygenassist_si128(rk2, 0x1);
    expand(&rk0, &rk1, &rk2);
    ctx->round_keys[1] = _mm_shuffle_pd(ctx->round_keys[1], rk0, 0);
    ctx->round_keys[2] = _mm_shuffle_pd(rk0, rk2, 1);
    rk1                = _mm_aeskeygenassist_si128(rk2, 0x2);
    expand(&rk0, &rk1, &rk2);
    ctx->round_keys[3] = rk0;
    ctx->round_keys[4] = rk2;
    rk1                = _mm_aeskeygenassist_si128(rk2, 0x4);
    expand(&rk0, &rk1, &rk2);
    ctx->round_keys[4] = _mm_shuffle_pd(ctx->round_keys[4], rk0, 0);
    ctx->round_keys[5] = _mm_shuffle_pd(rk0, rk2, 1);
    rk1                = _mm_aeskeygenassist_si128(rk2, 0x8);
    ctx->round_keys[6] = rk0;
    ctx->round_keys[7] = rk2;
    rk1                = _mm_aeskeygenassist_si128(rk2, 0x10);
    expand(&rk0, &rk1, &rk2);
    ctx->round_keys[7] = _mm_shuffle_pd(ctx->round_keys[7], rk0, 0);
    ctx->round_keys[8] = _mm_shuffle_pd(rk0, rk2, 1);
    rk1                = _mm_aeskeygenassist_si128(rk2, 0x20);
    expand(&rk0, &rk1, &rk2);
    ctx->round_keys[9]  = rk0;
    ctx->round_keys[10] = rk2;
    rk1                 = _mm_aeskeygenassist_si128(rk2, 0x40);
    expand(&rk0, &rk1, &rk2);
    ctx->round_keys[10] = _mm_shuffle_pd(ctx->round_keys[10], rk0, 0);
    ctx->round_keys[11] = _mm_shuffle_pd(rk0, rk2, 1);
    rk1                 = _mm_aeskeygenassist_si128(rk2, 0x80);
    expand(&rk0, &rk1, &rk3);
    ctx->round_keys[12] = rk0;

    return CCERR_OK;
}

#endif
