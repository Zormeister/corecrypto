//
//  cc_muxp.c
//  corecrypto
//
//  Created by Zormeister on 2/7/25.
//

#include <corecrypto/cc_priv.h>

void *cc_muxp(int s, const void *a, const void *b)
{
    if (s) {
        return __DECONST(void *, a);
    } else {
        return __DECONST(void *, b);
    }
}
