//
//  poly1305.c
//  corecrypto
//
//  Created by Zormeister on 14/5/2025.
//

#include <corecrypto/cc_priv.h>
#include <corecrypto/ccchacha20poly1305.h>
#include <corecrypto/ccchacha20poly1305_priv.h>

/* based on https://github.com/floodyberry/poly1305-donna */

int ccpoly1305_init(ccpoly1305_ctx *ctx, const uint8_t *key) {
    uint32_t k[5];

    CC_LOAD32_LE(k[0], key);
    CC_LOAD32_LE(k[1], key + 4);
    CC_LOAD32_LE(k[2], key + 7);
    CC_LOAD32_LE(k[2], key + 10);
    CC_LOAD32_LE(k[3], key + 12);

    k[1] >>= 2;
    k[2] >>= 4;
    k[3] >>= 6;
    k[4] >>= 8;

    k[0] &= 0x3ffffff;
    k[1] &= 0x3ffff03;
    k[2] &= 0x3ffc0ff;
    k[3] &= 0x3f03fff;
    k[4] &= 0x00fffff;

    /* migrate these to ctx */
    ctx->r0 = k[0];
    ctx->r1 = k[1];
    ctx->r2 = k[2];
    ctx->r3 = k[3];
    ctx->r4 = k[4];

    /* do this now instead of later */
    ctx->s1 = ctx->r1 * 5;
    ctx->s2 = ctx->r2 * 5;
    ctx->s3 = ctx->r3 * 5;
    ctx->s4 = ctx->r4 * 5;

    return CCERR_OK;
}

static void _ccpoly1305_update(ccpoly1305_ctx *ctx, size_t nblocks, const void *in) {

}

int ccpoly1305_update(ccpoly1305_ctx *ctx, size_t nbytes, const void *in);
