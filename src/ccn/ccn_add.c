//
//  ccn_add.c
//  corecrypto
//
//  Created by Zormeister on 9/6/2025.
//

#include "ccn_internal.h"
#include <corecrypto/cc_priv.h>
#include <corecrypto/ccn.h>

cc_unit ccn_add(cc_size n, cc_unit *r, const cc_unit *s, const cc_unit *t)
{
#if CCN_ADD_ASM
    return ccn_add_asm(n, r, s, t);
#else
    cc_unit carry = 0;

    for (int i = 0; i < n; i++) {
        cc_unit u = s[i] + t[i] + carry;
        if (u < s[i] || u == s[i] && carry) {
            carry = 1;
        } else {
            carry = 0;
        }

        r[i] = u;
    }

    return carry;
#endif
}
