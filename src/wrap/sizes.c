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

#include <corecrypto/cc.h>
#include <corecrypto/cc_priv.h>
#include <corecrypto/ccaes.h>
#include <corecrypto/ccwrap.h>
#include <corecrypto/ccwrap_priv.h>

// Wrapped Key includes the included wrapped IV.
// The formula is literally just key_len + CCWRAP_SEMIBLOCK as the IV is limited to being a 64-bit value.
size_t ccwrap_wrapped_size(size_t size)
{
    return size + CCWRAP_SEMIBLOCK;
}

// The same applies here.
size_t ccwrap_unwrapped_size(size_t size)
{
    // Avoid integer overflow
    if (size < CCWRAP_SEMIBLOCK) {
        return 0;
    }
    return size - CCWRAP_SEMIBLOCK;
}
