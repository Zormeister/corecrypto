//
//  ccaes_intel_cbc_decrypt_opt_mode.c
//  corecrypto
//
//  Created by Zormeister on 8/7/25.
//

#include <corecrypto/ccaes.h>

#if CCAES_INTEL_ASM

struct ccaes_intel_opt_key {
    uint32_t key[60];
    uint32_t rounds;
};

extern void AESExpandKeyForEncryption(uint32_t *expanded_key, const uint32_t *key, long key_size);
extern void AESEncryptCBC(void *out, const void *in, void *iv, const uint32_t *expanded_key, long nblocks, int nrounds);

static int cbc_opt_wrapper_init(const struct ccmode_cbc *ecb, cccbc_ctx *ctx, size_t key_len, const void *key)
{
    struct ccaes_intel_opt_key *k = (struct ccaes_intel_opt_key *)ctx;
    AESExpandKeyForEncryption(k->key, key, key_len / sizeof(uint32_t));
    switch (key_len) {
        case CCAES_KEY_SIZE_128:
            k->rounds = 10;
            break;
        case CCAES_KEY_SIZE_192:
            k->rounds = 12;
            break;
        case CCAES_KEY_SIZE_256:
            k->rounds = 14;
            break;
    }
    return 0;
}

static int cbc_opt_wrapper_enc(const cccbc_ctx *ctx, cccbc_iv *iv, size_t nblocks, const void *in, void *out)
{
    struct ccaes_intel_opt_key *k = (struct ccaes_intel_opt_key *)ctx;
    AESEncryptCBC(out, in, iv->b, k->key, nblocks, k->rounds);
    return 0;
}

const struct ccmode_cbc ccaes_intel_cbc_encrypt_opt_mode = {
    .size       = ccn_sizeof_size(sizeof(struct ccaes_intel_opt_key)),
    .block_size = CCAES_BLOCK_SIZE,
    .init       = cbc_opt_wrapper_init,
    .cbc        = cbc_opt_wrapper_enc
};

#endif
