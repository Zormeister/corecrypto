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
    cc_try_abort("wip.");

    /* TODO: regular impl */
    return 0;
#endif
}
