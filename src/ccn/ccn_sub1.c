//
//  ccn_sub1.c
//  corecrypto
//
//  Created by Zormeister on 30/7/2025.
//

#include "ccn_internal.h"
#include <corecrypto/cc_priv.h>
#include <corecrypto/ccn.h>

cc_unit ccn_sub1(cc_size n, cc_unit *r, const cc_unit *s, const cc_unit v)
{
    /* can we try and avoid breaking things */
    if (n == 0) {
        return 0;
    }

    /* use ccn_add - it just works */
    cc_unit tmp[n];
    ccn_zero(n, tmp);
    tmp[0] = v;
    return ccn_sub(n, r, s, tmp);
}
