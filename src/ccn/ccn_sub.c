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

#include "ccn_internal.h"
#include <corecrypto/cc_priv.h>
#include <corecrypto/ccn.h>

cc_unit ccn_sub(cc_size n, cc_unit *r, const cc_unit *s, const cc_unit *t)
{
#if CCN_ADD_ASM
    return ccn_sub_asm(n, r, s, t);
#else
    cc_unit borrow = 0;

    for (int i = 0; i < n; i++) {
        cc_unit u = s[i];

        /* first, handle any borrow that may be needed */
        if (borrow) {
            /* borrow flag, because this is absoultely a disaster. */
            if (u > 0) {
                borrow = 0; /* no borrowing here */
            }

            u -= 1;
        }

        if (u < t[i]) {
            borrow = 1;
        }

        u -= t[i];

        r[i] = u;
    }

    return borrow;
#endif
}
