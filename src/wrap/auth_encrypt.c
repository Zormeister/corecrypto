//
//  auth_encrypt.c
//  corecrypto
//
//  Created by Zormeister on 27/1/2025.
//

#include <corecrypto/cc.h>
#include <corecrypto/cc_priv.h>
#include <corecrypto/ccaes.h>
#include <corecrypto/ccwrap.h>
#include <corecrypto/ccwrap_priv.h>

int ccwrap_auth_encrypt_withiv(struct ccmode_ecb *mode, ccecb_ctx *context, size_t key_length, const uint8_t *key, size_t *wrapped_key_length, uint8_t *wrapped_key, const uint8_t *iv)
{
    uint64_t R[(key_length / CCWRAP_SEMIBLOCK) + 1]; // + 1 for the outgoing IV.
    uint64_t B;
    size_t n = (key_length / CCWRAP_SEMIBLOCK);

    if (key_length != CCAES_KEY_SIZE_128) {
        return CCERR_PARAMETER;
    }

    uint64_t A = *(uint64_t *)iv;
    R[0] = A;
    for (int i = 1; i < n; i++) {
        R[i] = key[i];
    }

    for (int j = 0; j < 5; j++) {
        for (int k = 1; k < n; k++) {
            uint64_t tmp = A | R[k];
            if (mode->ecb(context, 1, &tmp, &B) == CCERR_OK) {
                A = CC_H2BE64(B) ^ (n * j) + k;
                R[k] = CC_H2LE64(B);
            } else {
                CC_MEMSET(R, 0, sizeof(R));
                return CCERR_INTERNAL;
            }
        }
    }

    *wrapped_key_length = ccwrap_wrapped_size(key_length);
    CC_MEMCPY(wrapped_key, R, ccwrap_wrapped_size(key_length));

    return CCERR_OK;
}

int ccwrap_auth_encrypt(struct ccmode_ecb *mode, ccecb_ctx *context, size_t key_length, const uint8_t *key, size_t *wrapped_key_length, uint8_t *wrapped_key)
{
    return ccwrap_auth_encrypt_withiv(mode, context, key_length, key, wrapped_key_length, wrapped_key, ccwrap_default_iv);
}
