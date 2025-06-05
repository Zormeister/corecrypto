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
#include <corecrypto/cc_config.h>

#if CORECRYPTO_TEST

enum {
    crypto_digest_md2 = 0,
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
    crypto_cipher_aes = 0,
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
    crypto_cipher_mode_cfb,
    crypto_cipher_mode_max,
} typedef crypto_cipher_mode_t;

typedef int (*cctest_digest_callback)(void);
typedef int (*cctest_cipher_callback)(void);

int cctest_run_all_tests(void);

int cctest_run_digest_tests(crypto_digest_type_t dgst);
int cctest_run_cipher_tests(crypto_cipher_type_t ciph, crypto_cipher_mode_t mode);

#endif /* CORECRYPTO_TEST */

#endif /* _CORECRYPTO_CCTEST_INTERNAL_H_ */

