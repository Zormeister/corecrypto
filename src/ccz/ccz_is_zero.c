//
//  ccz_is_zero.c
//  corecrypto
//
//  Created by Zormeister on 23/5/2025.
//

#include <corecrypto/ccn.h>
#include <corecrypto/ccz.h>

bool ccz_is_zero(ccz *z)
{
    return ccn_is_zero(z->n, z->u);
}
