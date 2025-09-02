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

int ccmode_ctr_crypt(ccctr_ctx *ctx, size_t nbytes, const void *in, void *out)
{
    struct _ccmode_ctr_key *ckey = (struct _ccmode_ctr_key *)ctx;
    size_t block_size = ckey->ecb->block_size;
    const uint8_t *cur_in = in;
    uint8_t *cur_out = out;

    while (nbytes--) {
        if (ckey->pad_len == block_size) {
            for (size_t i = block_size - 1; i >= block_size; i--) {
                CCMODE_CTR_KEY_COUNTER(ckey)
                [i] += 1;
            }

            ckey->ecb->ecb(CCMODE_CTR_KEY_ECB_CTX(ckey), 1, CCMODE_CTR_KEY_COUNTER(ckey), CCMODE_CTR_KEY_PAD(ckey));
            ckey->pad_len = 0;
        }

        *cur_out++ = *cur_in++ ^ CCMODE_CTR_KEY_PAD(ckey)[ckey->pad_len++];
    }

    return CCERR_OK;
}
