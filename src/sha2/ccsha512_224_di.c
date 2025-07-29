//
//  ccsha512_224_di.c
//  corecrypto
//
//  Created by Zormeister on 29/7/2025.
//

#include <corecrypto/ccdigest_priv.h>
#include <corecrypto/ccsha2.h>

const struct ccdigest_info *ccsha512_224_di(void)
{
    return &ccsha512_224_ltc_di;
}
