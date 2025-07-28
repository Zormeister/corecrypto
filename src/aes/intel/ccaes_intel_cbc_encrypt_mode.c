//
//  ccaes_intel_cbc_encrypt_mode.c
//  corecrypto
//
//  Created by Zormeister on 8/7/25.
//

#include <corecrypto/ccaes.h>

#if CCAES_INTEL_ASM

#include "vng_aes_intel.h"

struct ccaes_intel_encrypt_key {
    vng_aes_intel_encrypt_ctx ctx[1];
} typedef ccaes_intel_encrypt_key;

static int init_wrapper_opt(const struct ccmode_cbc *ecb, cccbc_ctx *ctx, size_t key_len, const void *key)
{
    struct ccaes_intel_encrypt_key *k = (struct ccaes_intel_encrypt_key *)ctx;
    vng_aes_encrypt_opt_key(key, key_len, k->ctx);
    return 0;
}

static int cbc_wrapper_opt(const cccbc_ctx *ctx, cccbc_iv *iv, size_t nblocks, const void *in, void *out)
{
    struct ccaes_intel_encrypt_key *k = (struct ccaes_intel_encrypt_key *)ctx;
    vng_aes_encrypt_opt_cbc(in, (unsigned char *)iv, nblocks, out, k->ctx);
    return 0;
}

const struct ccmode_cbc ccaes_intel_cbc_encrypt_opt_mode = {
    .size = sizeof(ccaes_intel_encrypt_key),
    .block_size = CCAES_BLOCK_SIZE,
    .init = init_wrapper_opt,
    .cbc = cbc_wrapper_opt,
    .custom = NULL,
};

static int init_wrapper_aesni(const struct ccmode_cbc *ecb, cccbc_ctx *ctx, size_t key_len, const void *key)
{
    struct ccaes_intel_encrypt_key *k = (struct ccaes_intel_encrypt_key *)ctx;
    vng_aes_encrypt_aesni_key(key, key_len, k->ctx);
    return 0;
}

static int cbc_wrapper_aesni(const cccbc_ctx *ctx, cccbc_iv *iv, size_t nblocks, const void *in, void *out)
{
    struct ccaes_intel_encrypt_key *k = (struct ccaes_intel_encrypt_key *)ctx;
    vng_aes_encrypt_aesni_cbc(in, (unsigned char *)iv, nblocks, out, k->ctx);
    return 0;
}

const struct ccmode_cbc ccaes_intel_cbc_encrypt_aesni_mode = {
    .size = sizeof(ccaes_intel_encrypt_key),
    .block_size = CCAES_BLOCK_SIZE,
    .init = init_wrapper_aesni,
    .cbc = cbc_wrapper_aesni,
    .custom = NULL,
};

#endif
