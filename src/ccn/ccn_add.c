//
//  ccn_add.c
//  corecrypto
//
//  Created by Zormeister on 9/6/2025.
//

#include <corecrypto/ccn.h>
#include <corecrypto/cc_priv.h>
#include "ccn_internal.h"

cc_unit ccn_add(cc_size n, cc_unit *r, const cc_unit *s, const cc_unit *t) {
#if CCN_ADD_ASM
    return ccn_add_asm(n, r, s, t);
#else
    cc_unit carry = 0;

    cc_abort("wip.");

    /* TODO: regular impl */
    return carry;
#endif
}

