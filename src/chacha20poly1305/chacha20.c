//
//  chacha20.c
//  corecrypto
//
//  Created by Zormeister on 11/2/2025.
//

#include <corecrypto/cc_priv.h>
#include <corecrypto/ccchacha20poly1305_priv.h>

/*
 * REFERENCE SOURCES:
 *  - https://datatracker.ietf.org/doc/html/rfc7539
 */

#define CHACHA_QUARTERROUND(context,a,b,c,d) \
    context->state[a] += context->state[b]; \
    context->state[d] ^= context->state[a]; \
    context->state[d] <<= 16; \
    context->state[c] += context->state[d]; \
    context->state[b] ^= context->state[c]; \
    context->state[b] <<= 12; \
    context->state[a] += context->state[b]; \
    context->state[d] ^= context->state[a]; \
    context->state[d] <<= 8; \
    context->state[c] += context->state[d]; \
    context->state[b] ^= context->state[c]; \
    context->state[b] <<= 7

static void run_chacha_rounds(ccchacha20_ctx *ctx) {
    CHACHA_QUARTERROUND(ctx, 0, 4, 8, 12);
    CHACHA_QUARTERROUND(ctx, 1, 5, 9, 13);
    CHACHA_QUARTERROUND(ctx, 2, 6, 10, 14);
    CHACHA_QUARTERROUND(ctx, 3, 7, 11, 15);
    CHACHA_QUARTERROUND(ctx, 0, 5, 10, 15);
    CHACHA_QUARTERROUND(ctx, 1, 6, 11, 12);
    CHACHA_QUARTERROUND(ctx, 2, 7, 8, 13);
    CHACHA_QUARTERROUND(ctx, 3, 4, 9, 14);
}

/*
 *  c = constant, k - key, b = counter, n = nonce
 *  cccccccc  cccccccc  cccccccc  cccccccc
 *  kkkkkkkk  kkkkkkkk  kkkkkkkk  kkkkkkkk
 *  kkkkkkkk  kkkkkkkk  kkkkkkkk  kkkkkkkk
 *  bbbbbbbb  nnnnnnnn  nnnnnnnn  nnnnnnnn
 */
static void ccchacha_init_state(ccchacha20_ctx *ctx, const void *key, const void *nonce, uint32_t counter) {
    
    // set our constants
    ctx->state[0] = 0x61707865;
    ctx->state[1] = 0x3320646e;
    ctx->state[2] = 0x79622d32;
    ctx->state[3] = 0x6b206574;
    // Copy the 8 bytes of key we need to state[4]
    // Should I worry about endianness? We're always going to be running on a LE system but IDK if I should future-proof this
    // Also - I *think* this can be prone to buffer overflows on the key and nonce - should I worry about that?
    CC_MEMCPY(&ctx->state[4], key, 8);
    // Copy over the nonce
    ctx->state[11] = counter;
    CC_MEMCPY(&ctx->state[12], nonce, 3);
}

int ccchacha20_block(ccchacha20_ctx *ctx) {
    uint32_t initial_state[16];

    if (ctx == NULL || ctx->state[0] == 0) {
        return CCERR_PARAMETER;
    }
    
    CC_MEMCPY(initial_state, ctx->state, CCCHACHA20_BLOCK_NBYTES);
    
    // Run the rounds
    uint8_t rounds = 10;
    while (rounds--) {
        run_chacha_rounds(ctx);
    }
    
    // "At the end of 20 rounds (or 10 iterations of the above list), we add
    // the original input words to the output words, and serialize the
    // result by sequencing the words one-by-one in little-endian order."
    for (int i = 0; i < 16; i++) {
        // Could I have just done this in the buffer?
        initial_state[i] += ctx->state[i];
    }
    
    CC_MEMCPY(ctx->state, initial_state, CCCHACHA20_BLOCK_NBYTES);

    return CCERR_OK;
}
    
int ccchacha20(const void *key, const void *nonce, uint32_t counter, size_t nbytes, const void *in, void *out) {
    // check that we have our required args
    if (key == NULL || nonce == NULL || in == NULL || out == NULL) {
        return CCERR_PARAMETER;
    }
    ccchacha20_ctx ctx;
    ccchacha_init_state(&ctx, key, nonce, counter);
    if (ccchacha20_block(&ctx) == CCERR_OK) {
        return CCERR_INTERNAL;
    }
    
    CC_MEMCPY(ctx.buffer, in, CCCHACHA20_BLOCK_NBYTES);
    
    // XOR the whole thing.
    cc_xor(CCCHACHA20_BLOCK_NBYTES, out, ctx.buffer, ctx.state);
    
    return CCERR_OK;
}
