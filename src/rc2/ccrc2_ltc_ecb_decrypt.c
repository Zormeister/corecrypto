//
//  ccrc2_ltc_ecb_decrypt.c
//  corecrypto
//
//  Created by Zormeister on 2/6/2025.
//

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

#include "ccrc2_ltc_internal.h"

int ccrc2_ltc_ecb_decrypt(const ccecb_ctx *ctx, size_t nblocks, const void *in, void *out)
{
    uint32_t x76, x54, x32, x10;
    struct ccrc2_ltc_ctx *ltc = (struct ccrc2_ltc_ctx *)ctx;
    const uint8_t *cur_in = in;
    uint8_t *cur_out = out;

    while (nblocks--) {
        x76 = ((unsigned)cur_in[7] << 8) + (unsigned)cur_in[6];
        x54 = ((unsigned)cur_in[5] << 8) + (unsigned)cur_in[4];
        x32 = ((unsigned)cur_in[3] << 8) + (unsigned)cur_in[2];
        x10 = ((unsigned)cur_in[1] << 8) + (unsigned)cur_in[0];

        for (int i = 15; i >= 0; i--) {
            if (i == 4 || i == 10) {
                x76 = (x76 - ltc->xkey[x54 & 63]) & 0xFFFF;
                x54 = (x54 - ltc->xkey[x32 & 63]) & 0xFFFF;
                x32 = (x32 - ltc->xkey[x10 & 63]) & 0xFFFF;
                x10 = (x10 - ltc->xkey[x76 & 63]) & 0xFFFF;
            }

            x76 = ((x76 << 11) | (x76 >> 5));
            x76 = (x76 - ((x10 & ~x54) + (x32 & x54) + ltc->xkey[4 * i + 3])) & 0xFFFF;

            x54 = ((x54 << 13) | (x54 >> 3));
            x54 = (x54 - ((x76 & ~x32) + (x10 & x32) + ltc->xkey[4 * i + 2])) & 0xFFFF;

            x32 = ((x32 << 14) | (x32 >> 2));
            x32 = (x32 - ((x54 & ~x10) + (x76 & x10) + ltc->xkey[4 * i + 1])) & 0xFFFF;

            x10 = ((x10 << 15) | (x10 >> 1));
            x10 = (x10 - ((x32 & ~x76) + (x54 & x76) + ltc->xkey[4 * i + 0])) & 0xFFFF;
        }

        cur_out[0] = (unsigned char)x10;
        cur_out[1] = (unsigned char)(x10 >> 8);
        cur_out[2] = (unsigned char)x32;
        cur_out[3] = (unsigned char)(x32 >> 8);
        cur_out[4] = (unsigned char)x54;
        cur_out[5] = (unsigned char)(x54 >> 8);
        cur_out[6] = (unsigned char)x76;
        cur_out[7] = (unsigned char)(x76 >> 8);
    }

    return CCERR_OK;
}
