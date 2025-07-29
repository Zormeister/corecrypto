//
//  ccaes_intel_ecb_encrypt_mode.c
//  corecrypto
//
//  Created by Zormeister on 10/5/25.
//

#include <corecrypto/ccaes.h>

#if CCAES_INTEL_ASM

#include "vng_aes_intel.h"

struct ccaes_intel_encrypt_key {
    vng_aes_intel_encrypt_ctx ctx[1];
} typedef ccaes_intel_encrypt_key;

static int init_wrapper_opt(const struct ccmode_ecb *ecb, ccecb_ctx *ctx, size_t key_len, const void *key)
{
    struct ccaes_intel_encrypt_key *k = (struct ccaes_intel_encrypt_key *)ctx;
    vng_aes_encrypt_opt_key(key, key_len, k->ctx);
    return 0;
}

static int ecb_wrapper_opt(const ccecb_ctx *ctx, size_t nblocks, const void *in, void *out)
{
    struct ccaes_intel_encrypt_key *k = (struct ccaes_intel_encrypt_key *)ctx;

    while (nblocks--) {
        vng_aes_encrypt_opt(in, out, k->ctx);
        in += CCAES_BLOCK_SIZE;
        out += CCAES_BLOCK_SIZE;
    }

    return 0;
}

const struct ccmode_ecb ccaes_intel_ecb_encrypt_opt_mode = {
    .size = sizeof(ccaes_intel_encrypt_key),
    .block_size = CCAES_BLOCK_SIZE,
    .init = init_wrapper_opt,
    .ecb = ecb_wrapper_opt,
};

static int init_wrapper_aesni(const struct ccmode_ecb *ecb, ccecb_ctx *ctx, size_t key_len, const void *key)
{
    struct ccaes_intel_encrypt_key *k = (struct ccaes_intel_encrypt_key *)ctx;
    vng_aes_encrypt_aesni_key(key, key_len, k->ctx);
    return 0;
}

static int ecb_wrapper_aesni(const ccecb_ctx *ctx, size_t nblocks, const void *in, void *out)
{
    struct ccaes_intel_encrypt_key *k = (struct ccaes_intel_encrypt_key *)ctx;

    while (nblocks--) {
        vng_aes_encrypt_aesni(in, out, k->ctx);
        in += CCAES_BLOCK_SIZE;
        out += CCAES_BLOCK_SIZE;
    }

    return 0;
}

const struct ccmode_ecb ccaes_intel_ecb_encrypt_aesni_mode = {
    .size = sizeof(ccaes_intel_encrypt_key),
    .block_size = CCAES_BLOCK_SIZE,
    .init = init_wrapper_aesni,
    .ecb = ecb_wrapper_aesni,
};

#endif
