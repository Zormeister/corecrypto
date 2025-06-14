//
//  ccz_is_zero.c
//  corecrypto
//
//  Created by Zormeister on 23/5/2025.
//

#include <corecrypto/ccz.h>
#include <corecrypto/ccn.h>

bool ccz_is_zero(ccz *z) {
    return ccn_is_zero(z->n, z->u);
}
