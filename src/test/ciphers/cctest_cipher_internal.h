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

#ifndef _CORECRYPTO_CCTEST_CIPHER_INTERNAL_H_
#define _CORECRYPTO_CCTEST_CIPHER_INTERNAL_H_

#include <corecrypto/cc.h>

enum {
    crypto_op_enc,
    crypto_op_dec,
} typedef crypto_op_t;

struct cctest_cipher_vector {
    const char *key;
    const char *pt;
    const char *ct;
    const char *iv;
};

#endif /* _CORECRYPTO_CCTEST_CIPHER_INTERNAL_H_ */
