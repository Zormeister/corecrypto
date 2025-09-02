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

int ccmode_cfb_init(const struct ccmode_cfb *cfb, cccfb_ctx *ctx, size_t rawkey_len, const void *rawkey,
                    const void *iv)
{
    struct _ccmode_cfb_key *ckey = (struct _ccmode_cfb_key *)ctx;
    ckey->ecb = (const struct ccmode_ecb *)cfb->custom;
    ckey->pad_len = 0;
    cc_memcpy(CCMODE_CFB_KEY_FEEDBACK(ckey), iv, ckey->ecb->block_size);
    ckey->ecb->init(ckey->ecb, CCMODE_CFB_KEY_ECB_CTX(ckey), rawkey_len, rawkey);
    return CCERR_OK;
}
