//
//  ccaes_intel_ecb_decrypt_opt_mode.c
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

extern void AESExpandKeyForDecryption(uint32_t *expanded_key, const uint32_t *key, long key_size);
extern void AESDecryptWithExpandedKey(void *out, const void *in, const uint32_t *expanded_key, int nrounds);

static int opt_wrapper_init(const struct ccmode_ecb *ecb, ccecb_ctx *ctx, size_t key_len, const void *key)
{
    struct ccaes_intel_opt_key *k = (struct ccaes_intel_opt_key *)ctx;
    AESExpandKeyForDecryption(k->key, key, key_len / sizeof(uint32_t));
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

static int opt_wrapper_dec(const ccecb_ctx *ctx, size_t nblocks, const void *in, void *out)
{
    struct ccaes_intel_opt_key *k = (struct ccaes_intel_opt_key *)ctx;
    while (nblocks--) {
        AESDecryptWithExpandedKey(out, in, k->key, k->rounds);
        out += CCAES_BLOCK_SIZE;
        in += CCAES_BLOCK_SIZE;
    }
    return 0;
}

const struct ccmode_ecb ccaes_intel_ecb_decrypt_opt_mode = {
    .size       = ccn_sizeof_size(sizeof(struct ccaes_intel_opt_key)),
    .block_size = CCAES_BLOCK_SIZE,
    .init       = opt_wrapper_init,
    .ecb        = opt_wrapper_dec
};

#endif
