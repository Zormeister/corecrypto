//
//  ccdh_gp_rfc2409group02.c
//  corecrypto
//
//  Created by Zormeister on 23/5/2025.
//

#include "ccdh_gp_decl.h"
#include <corecrypto/ccn.h>

ccdh_gp_decl_n(1024) _ccdh_gp_rfc2409group02 = {
    .hd.n = ccn_nof(1024),
    .hd.options = 0,
    .p = {
        CCN64_C(FF, FF, FF, FF, FF, FF, FF, FF),
        /* i uh. i'll fill this in eventually. once i dump the memory of the GPs. */
    },
};