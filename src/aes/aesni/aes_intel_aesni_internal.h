//
//  aes_intel_aesni_internal.h
//  corecrypto
//
//  Created by Zormeister on 4/5/2025.
//

#ifndef _CORECRYPTO_CC_AES_INTEL_AESNI_INTERNAL_H_
#define _CORECRYPTO_CC_AES_INTEL_AESNI_INTERNAL_H_

#include <corecrypto/ccaes.h>

#if CCAES_INTEL_ASM

#include <wmmintrin.h>
#include <immintrin.h>
#include <mmintrin.h>

/* I know the macro is 'ASM' but I'd rather use compiler intrinsics. */

struct ccaes_intel_aesni_ctx {
    int nrounds;
    __m128i round_keys[15]; /* AES can have a maximum of fourteen rounds. */
};

/* TODO: AES-192 Round Key generation. */
/* As of right now this technically only supports AES-128 and AES-256. */
int ccaes_intel_aesni128_gen_round_keys(struct ccaes_intel_aesni_ctx *ctx);
int ccaes_intel_aesni192_gen_round_keys(struct ccaes_intel_aesni_ctx *ctx);
int ccaes_intel_aesni256_gen_round_keys(struct ccaes_intel_aesni_ctx *ctx);
int ccaes_intel_aesni_expand_key(struct ccaes_intel_aesni_ctx *ctx, size_t key_len, const void *key);

__m128i ccaes_intel_aesni_run_cipher_encrypt(struct ccaes_intel_aesni_ctx *ctx, __m128i state);
__m128i ccaes_intel_aesni_run_cipher_decrypt(struct ccaes_intel_aesni_ctx *ctx, __m128i state);

#endif

#endif /* _CORECRYPTO_CC_AES_INTEL_AESNI_INTERNAL_H_ */
