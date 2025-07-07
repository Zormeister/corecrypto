//
//  ccdh_gp_rfc2409group02.c
//  corecrypto
//
//  Created by Zormeister on 23/5/2025.
//

#include "ccdh_gp_decl.h"
#include <corecrypto/ccn.h>

ccdh_gp_decl_n(1024) _ccdh_gp_rfc2409group02 = {
    .ccn_size = ccn_nof(1024),
    .bitlen = ccn_bitsof_size(1024),
    .p = {
        CCN64_C(FF, FF, FF, FF, FF, FF, FF, FF),
        /* i uh. i'll fill this in eventually. once i dump the memory of the GPs. */
    },
};