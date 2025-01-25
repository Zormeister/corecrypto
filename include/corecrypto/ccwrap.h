//
//  ccwrap.h
//  corecrypto
//
//  Created by Zormeister on 22/1/2025.
//

#ifndef _CORECRYPTO_CCWRAP_H_
#define _CORECRYPTO_CCWRAP_H_

#include <corecrypto/ccmode.h>

/* AES wrapping stuff, RFC 3394 */

/* sizeof-s */

// I doubt this is *supposed* to be "public". Whatever.
#define CCWRAP_SEMIBLOCK 8 // AES 128-bit, according to NIST 800-38F

size_t ccwrap_wrapped_size(size_t key_length);
size_t ccwrap_unwrapped_size(size_t wrapped_length);

// Runtime check that ECB mode is AES-128?
int ccwrap_auth_encrypt_withiv(struct ccmode_ecb *mode, struct ccecb_ctx *context, size_t key_length, const uint8_t *key, size_t *wrapped_key_length, uint8_t *wrapped_key, const uint8_t *iv);

int ccwrap_auth_decrypt_withiv(struct ccmode_ecb *mode, struct ccecb_ctx *context, size_t wrapped_key_length, const uint8_t *wrapped_key, size_t *key_length, uint8_t *key, const uint8_t *iv);

/* The IV setup is weird for AES Key Wrapping, I think the way it's done is that the RFC 3394 IV gets used second after the first IV is used to encrypt the key */

/*
 * CommonCrypto reference:
 * for (i = 0; i < 2; i += 1) {
 *     if (ivs[i] == NULL) {
 *         continue;
 *     }
 *
 *     * ccwrap_auth_decrypt_withiv modifies this out parameter, so we need to set it on each iteration *
 *     tmpRawKeyLen = *rawKeyLen;
 *
 *     if (ccwrap_auth_decrypt_withiv(ccmode, ctx, wrappedKeyLen, wrappedKey, &tmpRawKeyLen, tmpRawKey, ivs[i]) == CCERR_OK) {
 *         err = kCCSuccess;
 *         break;
 *     }
 * }
 */

#endif /* _CORECRYPTO_CCWRAP_H_ */
