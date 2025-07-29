//
//  ccn_sub.c
//  corecrypto
//
//  Created by Zormeister on 16/6/2025.
//

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
