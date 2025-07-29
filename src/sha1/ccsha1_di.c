//
//  ccsha1_di.c
//  corecrypto
//
//  Created by Zormeister on 29/7/2025.
//

#include <corecrypto/ccsha1.h>

/* prefer the LTC implementation? I don't even know what would trigger the other one to be used. */
const struct ccdigest_info *ccsha1_di(void)
{
    return &ccsha1_ltc_di;
}
