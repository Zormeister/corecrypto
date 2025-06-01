//
//  ccsha256_di.c
//  corecrypto
//
//  Created by Zormeister on 27/5/2025.
//

#include <corecrypto/ccsha2.h>
#include <corecrypto/ccdigest_priv.h>

const struct ccdigest_info *ccsha256_di(void) {
    return &ccsha256_ltc_di;
}
