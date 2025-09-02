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

#include <corecrypto/cc_priv.h>
#include <corecrypto/ccn.h>

cc_size ccn_bitlen(cc_size n, const cc_unit *s)
{
    cc_size avail = ccn_n(n, s);
    cc_size size = ccn_bitsof_n(avail);

    cc_unit u = s[avail - 1];

#if CCN_UNIT_SIZE == 8
    size -= cc_clz64(u);
#else
    size -= cc_clz32(ccn32_32_parse(s, avail - 1));
#endif

    return size;
}
