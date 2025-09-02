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

#include "ccsha2_ltc_internal.h"
#include <corecrypto/ccdigest_priv.h>
#include <corecrypto/ccsha2.h>

const struct ccdigest_info ccsha512_256_ltc_di = {
    .output_size = CCSHA512_256_OUTPUT_SIZE,
    .state_size = CCSHA512_256_STATE_SIZE,
    .block_size = CCSHA512_256_BLOCK_SIZE,

    .oid_size = ccoid_sha512_256_len,
    .oid = CC_DIGEST_OID_SHA512_256,

    .initial_state = ccsha512_256_initial_state,

    .compress = ccsha512_ltc_compress,
    .final = ccsha512_final,
};
