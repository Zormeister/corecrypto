//
//  ccdh_gp_rfc2409group02.c
//  corecrypto
//
//  Created by Zormeister on 23/5/2025.
//

#include "ccdh_gp_decl.h"
#include <corecrypto/ccn.h>

/*
 
 FFFFFFFFFFFFFFFF
 C90FDAA22168C234
 C4C6628B80DC1CD1
 29024E088A67CC74
 020BBEA63B139B22
 514A08798E3404DD
 EF9519B3CD3A431B
 302B0A6DF25F1437
 4FE1356D6D51C245
 E485B576625E7EC6
 F44C42E9A637ED6B
 0BFF5CB6F406B7ED
 EE386BFB5A899FA5
 AE9F24117C4B1FE6
 49 28 66 51 EC E6 53 81
 FFFFFFFFFFFFFFF
 
 */

ccdh_gp_decl_n(1024) _ccdh_gp_rfc2409group02 = {
    .ccn_size = ccn_nof(1024),
    .bitlen = ccn_bitsof_size(1024),
    .p = {
        /* So the GPs are stored in reverse order. which makes sense considering the values are in BE. at least I think they are. */
        CCN64_C(FF, FF, FF, FF, FF, FF, FF, FF),
        CCN64_C(49, 28, 66, 51, EC, E6, 53, 81),
    },
};
