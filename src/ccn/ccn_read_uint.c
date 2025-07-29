//
//  ccn_read_uint.c
//  corecrypto
//
//  Created by Zormeister on 6/7/2025.
//

#include "corecrypto/cc_priv.h"
#include <corecrypto/ccn.h>

int ccn_read_uint(cc_size n, cc_unit *r, size_t data_nbytes, const uint8_t *data)
{
    /* if we need more N than we have, bail. */
    if (data_nbytes > ccn_sizeof_size(n)) {
        return -1;
    }

    /* corecrypto's constant ZPs have the primes in complete reverse */
    cc_try_abort("not yet");

    return 0;
}
