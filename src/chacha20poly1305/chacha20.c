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

/* Welcome to hell. My code is broken and I don't know why. */
/* Give me a month */

#define CHACHA_QUARTERROUND(state,a,b,c,d) \
    state[a] += state[b]; \
    state[d] ^= state[a]; \
    state[d] <<= 16; \
    state[c] += state[d]; \
    state[b] ^= state[c]; \
    state[b] <<= 12; \
    state[a] += state[b]; \
    state[d] ^= state[a]; \
    state[d] <<= 8; \
    state[c] += state[d]; \
    state[b] ^= state[c]; \
    state[b] <<= 7

static void run_chacha_round(uint32_t *s) {
    CHACHA_QUARTERROUND(s, 0, 4, 8, 12);
    CHACHA_QUARTERROUND(s, 1, 5, 9, 13);
    CHACHA_QUARTERROUND(s, 2, 6, 10, 14);
    CHACHA_QUARTERROUND(s, 3, 7, 11, 15);
    CHACHA_QUARTERROUND(s, 0, 5, 10, 15);
    CHACHA_QUARTERROUND(s, 1, 6, 11, 12);
    CHACHA_QUARTERROUND(s, 2, 7, 8, 13);
    CHACHA_QUARTERROUND(s, 3, 4, 9, 14);
}

/*
 *  c = constant, k - key, b = counter, n = nonce
 *  cccccccc  cccccccc  cccccccc  cccccccc
 *  kkkkkkkk  kkkkkkkk  kkkkkkkk  kkkkkkkk
 *  kkkkkkkk  kkkkkkkk  kkkkkkkk  kkkkkkkk
 *  bbbbbbbb  nnnnnnnn  nnnnnnnn  nnnnnnnn
 */

int ccchacha20_init(ccchacha20_ctx *ctx, const uint8_t *key) {
    if (ctx == NULL || key == NULL) {
        return CCERR_PARAMETER;
    }
    
    if (ctx->state[0] != 0) {
        return CCERR_CALL_SEQUENCE;
    }

    // Setup the constants
    ctx->state[0] = CC_H2LE32(0x61707865);
    ctx->state[1] = CC_H2LE32(0x3320646e);
    ctx->state[2] = CC_H2LE32(0x79622d32);
    ctx->state[3] = CC_H2LE32(0x6b206574);

    // Copy the 8 bytes of key we need to state[4]
    // Should I worry about endianness? We're always going to be running on a LE system but IDK if I should future-proof this
    CC_MEMCPY(&ctx->state[4], key, 8);
    CC_WRITE_LE32(&ctx->state[4], *(uint32_t *)(key));
    CC_WRITE_LE32(&ctx->state[5], *(uint32_t *)(key + 4));
    CC_WRITE_LE32(&ctx->state[6], *(uint32_t *)(key + 8));
    CC_WRITE_LE32(&ctx->state[7], *(uint32_t *)(key + 12));
    CC_WRITE_LE32(&ctx->state[8], *(uint32_t *)(key + 16));
    CC_WRITE_LE32(&ctx->state[9], *(uint32_t *)(key + 20));
    CC_WRITE_LE32(&ctx->state[10], *(uint32_t *)(key + 24));
    CC_WRITE_LE32(&ctx->state[11], *(uint32_t *)(key + 28));

    return CCERR_OK;
}

int ccchacha20_setcounter(ccchacha20_ctx *ctx, uint32_t counter) {
    if (ctx == NULL) {
        return CCERR_PARAMETER;
    }

    ctx->state[11] = CC_H2LE32(counter);

    return CCERR_OK;
}

int ccchacha20_setnonce(ccchacha20_ctx *ctx, const uint8_t *nonce) {
    if (ctx == NULL || nonce == NULL) {
        return CCERR_PARAMETER;
    }

    if (&ctx->state[13] == 0) {
        // big endian considerations?
        CC_WRITE_LE32(&ctx->state[13], *(uint32_t *)(nonce));
        CC_WRITE_LE32(&ctx->state[14], *(uint32_t *)(nonce + 4));
        CC_WRITE_LE32(&ctx->state[15], *(uint32_t *)(nonce + 8));
    } else {
        return CCERR_CALL_SEQUENCE;
    }

    return CCERR_OK;
}

int ccchacha20_update(ccchacha20_ctx *ctx, size_t nbytes, const void *in, void *out) {
    uint32_t tmp_state[16];
    size_t nblocks = 1;
    size_t remain = nbytes;

    if (ctx == NULL || in == NULL || out == NULL) {
        return CCERR_PARAMETER;
    }

    if ((nbytes % CCCHACHA20_BLOCK_NBYTES) == 0) {
        nblocks = nbytes / CCCHACHA20_BLOCK_NBYTES;
    } else {
        while ((remain -= CCCHACHA20_BLOCK_NBYTES) >= 64) {
            nblocks++;
        }
    }
    
    // 8 QRounds, 2 rounds per run, 10 * 2 = 20 rounds
    for (int i = 1; i <= nblocks; i++) {
        // Setup variables
        size_t size = CCCHACHA20_BLOCK_NBYTES;
        if (i == nblocks && remain) {
            size = remain;
        }
        uint8_t *outptr = ((uint8_t *)out) + (i * CCCHACHA20_BLOCK_NBYTES);
        const uint8_t *inptr = ((const uint8_t *)in) + (i * CCCHACHA20_BLOCK_NBYTES);
        if (size == CCCHACHA20_BLOCK_NBYTES) {
            CC_WRITE_LE64(ctx->buffer, *(uint64_t *)inptr); // 0 - 7
            CC_WRITE_LE64(ctx->buffer + 8, *(((uint64_t *)inptr) + 8)); // 8 - 15
            CC_WRITE_LE64(ctx->buffer + 16, *(((uint64_t *)inptr) + 16)); // 16 - 23
            CC_WRITE_LE64(ctx->buffer + 24, *(((uint64_t *)inptr) + 24)); // 24 - 31
            CC_WRITE_LE64(ctx->buffer + 32, *(((uint64_t *)inptr) + 32)); // 32 - 39
            CC_WRITE_LE64(ctx->buffer + 40, *(((uint64_t *)inptr) + 40)); // 40 - 47
            CC_WRITE_LE64(ctx->buffer + 48, *(((uint64_t *)inptr) + 48)); // 48 - 55
            CC_WRITE_LE64(ctx->buffer + 56, *(((uint64_t *)inptr) + 56)); // 56 - 63
        } else {
            // i cheaped out. if anyone wants to fix this go ahead.
            CC_MEMCPY(ctx->buffer, inptr, size);
        }
        
        // Compute state
        // for BE: this should already be little endian, right?
        CC_MEMCPY(tmp_state, ctx->state, CCCHACHA20_BLOCK_NBYTES);
        for (int r = 0; r < 10; r++) {
            run_chacha_round(tmp_state);
        }
        
        for (int s = 0; s < 16; s++) {
            tmp_state[s] += ctx->state[s];
        }
        
        // XOR it.
        cc_xor(CCCHACHA20_BLOCK_NBYTES, ctx->buffer, inptr, tmp_state);
        ctx->state[12]++; // Increment counter.
        if (size == CCCHACHA20_BLOCK_NBYTES) {
            CC_WRITE_LE64(outptr, (uint64_t)ctx->buffer[0]); // 0 - 7
            CC_WRITE_LE64(outptr + 8, (uint64_t)ctx->buffer[8]); // 8 - 15
            CC_WRITE_LE64(outptr + 16, (uint64_t)ctx->buffer[16]); // 16 - 23
            CC_WRITE_LE64(outptr + 24, (uint64_t)ctx->buffer[24]); // 24 - 31
            CC_WRITE_LE64(outptr + 32, (uint64_t)ctx->buffer[32]); // 32 - 39
            CC_WRITE_LE64(outptr + 40, (uint64_t)ctx->buffer[40]); // 40 - 47
            CC_WRITE_LE64(outptr + 48, (uint64_t)ctx->buffer[48]); // 48 - 55
            CC_WRITE_LE64(outptr + 56, (uint64_t)ctx->buffer[56]); // 56 - 63
        } else {
            // i cheaped out. if anyone wants to fix this go ahead.
            cc_memcpy(outptr, ctx->buffer, size);
        }
        cc_clear(CCCHACHA20_BLOCK_NBYTES, ctx->buffer);
        cc_clear(16, tmp_state);
    }
    
    return CCERR_OK;
}

// Is this really all it does?
// It doesn't even wipe the nonce.
int ccchacha20_reset(ccchacha20_ctx *ctx) {

    ccchacha20_setcounter(ctx, 0); // reset counter

    return CCERR_OK;
}

int ccchacha20_final(ccchacha20_ctx *ctx) {
    cc_clear(sizeof(*ctx), ctx);
    return CCERR_OK;
};
    
int ccchacha20(const void *key, const void *nonce, uint32_t counter, size_t nbytes, const void *in, void *out) {
    // check that we have our required args
    if (key == NULL || nonce == NULL || in == NULL || out == NULL) {
        return CCERR_PARAMETER;
    }
    ccchacha20_ctx ctx;

    ccchacha20_init(&ctx, key);
    ccchacha20_setnonce(&ctx, nonce);
    ccchacha20_setcounter(&ctx, counter);
    ccchacha20_update(&ctx, nbytes, in, out);
    ccchacha20_final(&ctx);

    return CCERR_OK;
}
