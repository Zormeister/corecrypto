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
#include <corecrypto/cc_priv.h>

int ccmode_cfb8_init(const struct ccmode_cfb8 *cfb, cccfb8_ctx *ctx, size_t rawkey_len, const void *rawkey,
                     const void *iv)
{
    struct _ccmode_cfb8_key *ckey = (struct _ccmode_cfb8_key *)ctx;
    ckey->ecb = (const struct ccmode_ecb *)cfb->custom;
    cc_memcpy(CCMODE_CFB8_KEY_FEEDBACK(ckey), iv, ckey->ecb->block_size);
    ckey->ecb->init(ckey->ecb, CCMODE_CFB8_KEY_ECB_CTX(ckey), rawkey_len, rawkey);
    ckey->ecb->ecb(CCMODE_CFB8_KEY_ECB_CTX(ckey), 1, CCMODE_CFB8_KEY_FEEDBACK(ckey), CCMODE_CFB8_KEY_PADDING(ckey));
    return CCERR_OK;
}
