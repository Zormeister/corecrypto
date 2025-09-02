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

#include "ccmode_internal.h"
#include <corecrypto/ccmode.h>
#include <corecrypto/ccmode_factory.h>

/* set the tweak (encrypt it to prep it for usage) */
int ccmode_xts_set_tweak(const ccxts_ctx *ctx, ccxts_tweak *tweak, const void *iv)
{
    struct _ccmode_xts_key *key = (struct _ccmode_xts_key *)ctx;
    struct _ccmode_xts_tweak *twk = (struct _ccmode_xts_tweak *)tweak;

    /* this is (hopefully) a new tweak */
    twk->blocks_processed = 0;

    /* encrypt the IV to create the tweak */
    ccecb_update(key->ecb_encrypt, CCMODE_XTS_KEY_ECB_ENCRYPT_CTX(key), 1, iv, &twk->u);

    return CCERR_OK;
}
