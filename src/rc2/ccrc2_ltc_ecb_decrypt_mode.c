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

#include "ccrc2_ltc_internal.h"
#include <corecrypto/ccn.h>

const struct ccmode_ecb ccrc2_ltc_ecb_decrypt_mode = {
    .size = ccn_nof_sizeof(struct ccrc2_ltc_ctx),
    .block_size = CCRC2_BLOCK_SIZE,
    .init = ccrc2_ltc_setup,
    .ecb = ccrc2_ltc_ecb_decrypt,
};
