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

#include "cctest_internal.h"
#include <corecrypto/cc_debug.h>
#include <corecrypto/cc_priv.h>

#if CORECRYPTO_TEST

cctest_digest_callback digests[crypto_digest_max];
cctest_cipher_callback ciphers[crypto_cipher_max][crypto_cipher_mode_max];

void cctest_init(void)
{
    cc_printf("cctest: initializing.\n");
}

#endif
