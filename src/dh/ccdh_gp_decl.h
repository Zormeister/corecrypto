//
//  ccdh_gp_decl.h
//  corecrypto
//
//  Created by Zormeister on 23/5/2025.
//

#ifndef _CORECRYPTO_CCDH_GP_DECL_H
#define _CORECRYPTO_CCDH_GP_DECL_H

#include <corecrypto/cczp.h>

#define ccdh_gp_decl_n(n) \
    struct { \
        struct cczp_hd hd; \
        cc_unit p[(n)]; /* consistent with CCZP */ \
        cc_unit r[(n)]; /* consistent with CCZP */ \
        cc_unit g[(n)]; \
        cc_unit q[(n)]; \
    }

#endif
