//
//  ccrc2_ltc_setup.c
//  corecrypto
//
//  Created by Zormeister on 2/6/2025.
//

#include "ccrc2_ltc_internal.h"

/* This is adapted from LibTomCrypt, created by Tom St Dennis, licensed under the Unlicense. */

/* I would like to thank him so much for the various bits and pieces reused for corecrypto. */

static const unsigned char permute[256] = {
    217, 120, 249, 196, 25, 221, 181, 237, 40, 233, 253, 121, 74, 160, 216, 157,
    198, 126, 55, 131, 43, 118, 83, 142, 98, 76, 100, 136, 68, 139, 251, 162,
    23, 154, 89, 245, 135, 179, 79, 19, 97, 69, 109, 141, 9, 129, 125, 50,
    189, 143, 64, 235, 134, 183, 123, 11, 240, 149, 33, 34, 92, 107, 78, 130,
    84, 214, 101, 147, 206, 96, 178, 28, 115, 86, 192, 20, 167, 140, 241, 220,
    18, 117, 202, 31, 59, 190, 228, 209, 66, 61, 212, 48, 163, 60, 182, 38,
    111, 191, 14, 218, 70, 105, 7, 87, 39, 242, 29, 155, 188, 148, 67, 3,
    248, 17, 199, 246, 144, 239, 62, 231, 6, 195, 213, 47, 200, 102, 30, 215,
    8, 232, 234, 222, 128, 82, 238, 247, 132, 170, 114, 172, 53, 77, 106, 42,
    150, 26, 210, 113, 90, 21, 73, 116, 75, 159, 208, 94, 4, 24, 164, 236,
    194, 224, 65, 110, 15, 81, 203, 204, 36, 145, 175, 80, 161, 244, 112, 57,
    153, 124, 58, 133, 35, 184, 180, 122, 252, 2, 54, 91, 37, 85, 151, 49,
    45, 93, 250, 152, 227, 138, 146, 174, 5, 223, 41, 16, 103, 108, 186, 201,
    211, 0, 230, 207, 225, 158, 168, 44, 99, 22, 1, 63, 88, 226, 137, 169,
    13, 56, 52, 27, 171, 51, 255, 176, 187, 72, 12, 95, 185, 177, 205, 46,
    197, 243, 219, 71, 229, 165, 156, 119, 10, 166, 32, 104, 254, 127, 193, 173
};

int ccrc2_ltc_setup(const struct ccmode_ecb *ecb, ccecb_ctx *ctx, size_t key_nbytes, const void *key)
{
    struct ccrc2_ltc_ctx *ltc = (struct ccrc2_ltc_ctx *)ctx;
    uint32_t bits = key_nbytes * 8;
    const uint8_t *k = key;
    unsigned char tmp[128];
    uint32_t T8, TM;
    int i;

    for (i = 0; i < key_nbytes; i++) {
        tmp[i] = k[i] & 255;
    }

    /* Phase 1: Expand input key to 128 bytes */
    if (key_nbytes < 128) {
        for (i = key_nbytes; i < 128; i++) {
            tmp[i] = permute[(tmp[i - 1] + tmp[i - key_nbytes]) & 255];
        }
    }

    /* Phase 2 - reduce effective key size to "bits" */
    T8 = (uint32_t)(bits + 7) >> 3;
    TM = (255 >> (uint32_t)(7 & -bits));
    tmp[128 - T8] = permute[tmp[128 - T8] & TM];
    for (i = 127 - T8; i >= 0; i--) {
        tmp[i] = permute[tmp[i + 1] ^ tmp[i + T8]];
    }

    /* Phase 3 - copy to xkey in little-endian order */
    for (i = 0; i < 64; i++) {
        ltc->xkey[i] = (uint32_t)tmp[2 * i] + ((uint32_t)tmp[2 * i + 1] << 8);
    }

    return CCERR_OK;
}
