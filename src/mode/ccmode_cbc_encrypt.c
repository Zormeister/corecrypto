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

int ccmode_cbc_encrypt(const cccbc_ctx *ctx, cccbc_iv *iv, size_t nblocks, const void *in, void *out)
{
    const struct _ccmode_cbc_key *fctx = (const struct _ccmode_cbc_key *)ctx;
    void *cur_iv = iv->b;

    /* iterate. */
    while (nblocks--) {
        cc_xor(ccecb_block_size(fctx->ecb), out, in, cur_iv);
        ccecb_update(fctx->ecb, CCMODE_CBC_KEY_ECB_CTX(fctx), 1, in, out);

        cur_iv = out;
        in += ccecb_block_size(fctx->ecb);
        out += ccecb_block_size(fctx->ecb);
    }

    return CCERR_OK;
}