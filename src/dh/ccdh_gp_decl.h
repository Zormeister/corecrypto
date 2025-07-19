//
//  ccdh_gp_decl.h
//  corecrypto
//
//  Created by Zormeister on 23/5/2025.
//

#ifndef _CORECRYPTO_CCDH_GP_DECL_H
#define _CORECRYPTO_CCDH_GP_DECL_H

#include <corecrypto/cczp.h>

#define ccdh_gp_decl_n(n)     \
    struct {                  \
        cc_size ccn_size;     \
        cc_unit bitlen;       \
        ccmod_func_t zp_func; \
        cc_unit p[(n)];       \
        cc_unit r[(n)];       \
        cc_unit g[(n)];       \
        cc_unit order[(n)];   \
        cc_unit l;            \
    }

#endif
