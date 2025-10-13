/*
 * Copyright (C) 2025 The PureDarwin Project, All rights reserved.
 *
 * @LICENSE_HEADER_BEGIN@
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * @LICENSE_HEADER_END@
 */

/*
 * Code adapted from LibTomCrypt, modular cryptographic library -- Tom St Denis
 *
 * LibTomCrypt is a library that provides various cryptographic
 * algorithms in a highly modular and flexible manner.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tomstdenis@gmail.com, http://libtom.org
 */

#include "ccmd5_internal.h"
#include <corecrypto/cc_config.h>
#include <corecrypto/ccdigest_priv.h>
#include <corecrypto/ccmd5.h>

#define F(x, y, z) (z ^ (x & (y ^ z)))
#define G(x, y, z) (y ^ (z & (y ^ x)))
#define H(x, y, z) (x ^ y ^ z)
#define I(x, y, z) (y ^ (x | (~z)))

#if CC_SMALL_CODE

#define FF(a, b, c, d, M, s, t)   \
    a = (a + F(b, c, d) + M + t); \
    a = CC_ROL(a, s) + b;

#define GG(a, b, c, d, M, s, t)   \
    a = (a + G(b, c, d) + M + t); \
    a = CC_ROL(a, s) + b;

#define HH(a, b, c, d, M, s, t)   \
    a = (a + H(b, c, d) + M + t); \
    a = CC_ROL(a, s) + b;

#define II(a, b, c, d, M, s, t)   \
    a = (a + I(b, c, d) + M + t); \
    a = CC_ROL(a, s) + b;

static const unsigned char Worder[64] = {
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
    1, 6, 11, 0, 5, 10, 15, 4, 9, 14, 3, 8, 13, 2, 7, 12,
    5, 8, 11, 14, 1, 4, 7, 10, 13, 0, 3, 6, 9, 12, 15, 2,
    0, 7, 14, 5, 12, 3, 10, 1, 8, 15, 6, 13, 4, 11, 2, 9
};

static const unsigned char Rorder[64] = {
    7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
    5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
    4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
    6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21
};

static const uint32_t Korder[64] = {
    0xd76aa478UL, 0xe8c7b756UL, 0x242070dbUL, 0xc1bdceeeUL, 0xf57c0fafUL, 0x4787c62aUL, 0xa8304613UL, 0xfd469501UL,
    0x698098d8UL, 0x8b44f7afUL, 0xffff5bb1UL, 0x895cd7beUL, 0x6b901122UL, 0xfd987193UL, 0xa679438eUL, 0x49b40821UL,
    0xf61e2562UL, 0xc040b340UL, 0x265e5a51UL, 0xe9b6c7aaUL, 0xd62f105dUL, 0x02441453UL, 0xd8a1e681UL, 0xe7d3fbc8UL,
    0x21e1cde6UL, 0xc33707d6UL, 0xf4d50d87UL, 0x455a14edUL, 0xa9e3e905UL, 0xfcefa3f8UL, 0x676f02d9UL, 0x8d2a4c8aUL,
    0xfffa3942UL, 0x8771f681UL, 0x6d9d6122UL, 0xfde5380cUL, 0xa4beea44UL, 0x4bdecfa9UL, 0xf6bb4b60UL, 0xbebfbc70UL,
    0x289b7ec6UL, 0xeaa127faUL, 0xd4ef3085UL, 0x04881d05UL, 0xd9d4d039UL, 0xe6db99e5UL, 0x1fa27cf8UL, 0xc4ac5665UL,
    0xf4292244UL, 0x432aff97UL, 0xab9423a7UL, 0xfc93a039UL, 0x655b59c3UL, 0x8f0ccc92UL, 0xffeff47dUL, 0x85845dd1UL,
    0x6fa87e4fUL, 0xfe2ce6e0UL, 0xa3014314UL, 0x4e0811a1UL, 0xf7537e82UL, 0xbd3af235UL, 0x2ad7d2bbUL, 0xeb86d391UL
};

#else

#define FF(a, b, c, d, M, s, t)   \
    a = (a + F(b, c, d) + M + t); \
    a = CC_ROLc(a, s) + b;

#define GG(a, b, c, d, M, s, t)   \
    a = (a + G(b, c, d) + M + t); \
    a = CC_ROLc(a, s) + b;

#define HH(a, b, c, d, M, s, t)   \
    a = (a + H(b, c, d) + M + t); \
    a = CC_ROLc(a, s) + b;

#define II(a, b, c, d, M, s, t)   \
    a = (a + I(b, c, d) + M + t); \
    a = CC_ROLc(a, s) + b;

#endif

static void md5_compress(ccdigest_state_t state, size_t nblocks, const void *buf)
{
    uint32_t i, W[16], a, b, c, d;
#if CC_SMALL_CODE
    uint32_t t;
#endif

    while (nblocks--) {

        /* copy the state into 512-bits into W[0..15] */
        for (i = 0; i < 16; i++) {
            CC_LOAD32_LE(W[i], buf + (4 * i));
        }

        /* copy state */
        a = ccdigest_u32(state)[0];
        b = ccdigest_u32(state)[1];
        c = ccdigest_u32(state)[2];
        d = ccdigest_u32(state)[3];

#if CC_SMALL_CODE
        for (i = 0; i < 16; ++i) {
            FF(a, b, c, d, W[Worder[i]], Rorder[i], Korder[i]);
            t = d;
            d = c;
            c = b;
            b = a;
            a = t;
        }

        for (; i < 32; ++i) {
            GG(a, b, c, d, W[Worder[i]], Rorder[i], Korder[i]);
            t = d;
            d = c;
            c = b;
            b = a;
            a = t;
        }

        for (; i < 48; ++i) {
            HH(a, b, c, d, W[Worder[i]], Rorder[i], Korder[i]);
            t = d;
            d = c;
            c = b;
            b = a;
            a = t;
        }

        for (; i < 64; ++i) {
            II(a, b, c, d, W[Worder[i]], Rorder[i], Korder[i]);
            t = d;
            d = c;
            c = b;
            b = a;
            a = t;
        }

#else
        FF(a, b, c, d, W[0], 7, 0xd76aa478UL)
        FF(d, a, b, c, W[1], 12, 0xe8c7b756UL)
        FF(c, d, a, b, W[2], 17, 0x242070dbUL)
        FF(b, c, d, a, W[3], 22, 0xc1bdceeeUL)
        FF(a, b, c, d, W[4], 7, 0xf57c0fafUL)
        FF(d, a, b, c, W[5], 12, 0x4787c62aUL)
        FF(c, d, a, b, W[6], 17, 0xa8304613UL)
        FF(b, c, d, a, W[7], 22, 0xfd469501UL)
        FF(a, b, c, d, W[8], 7, 0x698098d8UL)
        FF(d, a, b, c, W[9], 12, 0x8b44f7afUL)
        FF(c, d, a, b, W[10], 17, 0xffff5bb1UL)
        FF(b, c, d, a, W[11], 22, 0x895cd7beUL)
        FF(a, b, c, d, W[12], 7, 0x6b901122UL)
        FF(d, a, b, c, W[13], 12, 0xfd987193UL)
        FF(c, d, a, b, W[14], 17, 0xa679438eUL)
        FF(b, c, d, a, W[15], 22, 0x49b40821UL)
        GG(a, b, c, d, W[1], 5, 0xf61e2562UL)
        GG(d, a, b, c, W[6], 9, 0xc040b340UL)
        GG(c, d, a, b, W[11], 14, 0x265e5a51UL)
        GG(b, c, d, a, W[0], 20, 0xe9b6c7aaUL)
        GG(a, b, c, d, W[5], 5, 0xd62f105dUL)
        GG(d, a, b, c, W[10], 9, 0x02441453UL)
        GG(c, d, a, b, W[15], 14, 0xd8a1e681UL)
        GG(b, c, d, a, W[4], 20, 0xe7d3fbc8UL)
        GG(a, b, c, d, W[9], 5, 0x21e1cde6UL)
        GG(d, a, b, c, W[14], 9, 0xc33707d6UL)
        GG(c, d, a, b, W[3], 14, 0xf4d50d87UL)
        GG(b, c, d, a, W[8], 20, 0x455a14edUL)
        GG(a, b, c, d, W[13], 5, 0xa9e3e905UL)
        GG(d, a, b, c, W[2], 9, 0xfcefa3f8UL)
        GG(c, d, a, b, W[7], 14, 0x676f02d9UL)
        GG(b, c, d, a, W[12], 20, 0x8d2a4c8aUL)
        HH(a, b, c, d, W[5], 4, 0xfffa3942UL)
        HH(d, a, b, c, W[8], 11, 0x8771f681UL)
        HH(c, d, a, b, W[11], 16, 0x6d9d6122UL)
        HH(b, c, d, a, W[14], 23, 0xfde5380cUL)
        HH(a, b, c, d, W[1], 4, 0xa4beea44UL)
        HH(d, a, b, c, W[4], 11, 0x4bdecfa9UL)
        HH(c, d, a, b, W[7], 16, 0xf6bb4b60UL)
        HH(b, c, d, a, W[10], 23, 0xbebfbc70UL)
        HH(a, b, c, d, W[13], 4, 0x289b7ec6UL)
        HH(d, a, b, c, W[0], 11, 0xeaa127faUL)
        HH(c, d, a, b, W[3], 16, 0xd4ef3085UL)
        HH(b, c, d, a, W[6], 23, 0x04881d05UL)
        HH(a, b, c, d, W[9], 4, 0xd9d4d039UL)
        HH(d, a, b, c, W[12], 11, 0xe6db99e5UL)
        HH(c, d, a, b, W[15], 16, 0x1fa27cf8UL)
        HH(b, c, d, a, W[2], 23, 0xc4ac5665UL)
        II(a, b, c, d, W[0], 6, 0xf4292244UL)
        II(d, a, b, c, W[7], 10, 0x432aff97UL)
        II(c, d, a, b, W[14], 15, 0xab9423a7UL)
        II(b, c, d, a, W[5], 21, 0xfc93a039UL)
        II(a, b, c, d, W[12], 6, 0x655b59c3UL)
        II(d, a, b, c, W[3], 10, 0x8f0ccc92UL)
        II(c, d, a, b, W[10], 15, 0xffeff47dUL)
        II(b, c, d, a, W[1], 21, 0x85845dd1UL)
        II(a, b, c, d, W[8], 6, 0x6fa87e4fUL)
        II(d, a, b, c, W[15], 10, 0xfe2ce6e0UL)
        II(c, d, a, b, W[6], 15, 0xa3014314UL)
        II(b, c, d, a, W[13], 21, 0x4e0811a1UL)
        II(a, b, c, d, W[4], 6, 0xf7537e82UL)
        II(d, a, b, c, W[11], 10, 0xbd3af235UL)
        II(c, d, a, b, W[2], 15, 0x2ad7d2bbUL)
        II(b, c, d, a, W[9], 21, 0xeb86d391UL)
#endif

        ccdigest_u32(state)[0] += a;
        ccdigest_u32(state)[1] += b;
        ccdigest_u32(state)[2] += c;
        ccdigest_u32(state)[3] += d;

        buf += CCMD5_BLOCK_SIZE;
    }
}

const struct ccdigest_info ccmd5_ltc_di = {
    .output_size = CCMD5_OUTPUT_SIZE,
    .state_size = CCMD5_STATE_SIZE,
    .block_size = CCMD5_BLOCK_SIZE,

    .oid_size = 10,
    .oid = CC_DIGEST_OID_MD5,

    .initial_state = ccmd5_initial_state,

    .compress = md5_compress,
    .final = ccdigest_final_64le,
};
