//
//  cctest_internal.h
//  corecrypto
//
//  Created by Zormeister on 30/5/2025.
//

#ifndef _CORECRYPTO_CCTEST_INTERNAL_H_
#define _CORECRYPTO_CCTEST_INTERNAL_H_

#include <stdint.h>
#include <corecrypto/cc.h>

enum {
    crypto_digest_md2,
    crypto_digest_md4,
    crypto_digest_md5,
    crypto_digest_rmd160,
    crypto_digest_sha1,
    crypto_digest_sha224,
    crypto_digest_sha256,
    crypto_digest_sha384,
    crypto_digest_sha512,
    crypto_digest_max,
} typedef crypto_digest_type_t;

enum {
    crypto_cipher_aes,
    crypto_cipher_blowfish,
    crypto_cipher_cast,
    crypto_cipher_des,
    crypto_cipher_tdes,
    crypto_cipher_rc2,
    crypto_cipher_rc4,
    crypto_cipher_max,
} typedef crypto_cipher_type_t;

enum {
    crypto_cipher_mode_ecb,
    crypto_cipher_mode_cbc,
    crypto_cipher_mode_ofb,
    crypto_cipher_mode_max,
} typedef crypto_cipher_mode_type_t;

typedef int (*cctest_digest_callback)(size_t data_len, const void *data);
typedef int (*cctest_cipher_callback)(size_t key_len, const void *key, const void *iv, size_t data_len, const void *data);

int cctest_run_all_tests(void);

int cctest_run_digest_tests(crypto_digest_type_t dgst);

#endif /* _CORECRYPTO_CCTEST_INTERNAL_H_ */

