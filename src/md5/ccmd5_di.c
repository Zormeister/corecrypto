//
//  ccmd5_di.c
//  corecrypto
//
//  Created by Zormeister on 29/7/2025.
//

#include <corecrypto/ccmd5.h>

const struct ccdigest_info *ccmd5_di(void)
{
    return &ccmd5_ltc_di;
}
