/*
 * Copyright (C) 2025 Zormeister and The PureDarwin project, All rights reserved.
 *
 * @LICENSE_HEADER_BEGIN@
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * @LICENSE_HEADER_END@
 */

#ifndef _CORECRYPTO_CCTEST_INTERNAL_H_
#define _CORECRYPTO_CCTEST_INTERNAL_H_

#include <corecrypto/cc.h>
#include <corecrypto/cc_config.h>
#include <stdint.h>

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
