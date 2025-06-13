//
//  ccn_n.c
//  corecrypto
//
//  Created by Zormeister on 9/6/2025.
//

#include <corecrypto/ccn.h>

/* I assume units are stored in a native order. */

cc_size ccn_n(cc_size n, const cc_unit *s) {
    cc_size size = 0; /* There cannot be 'zero' units. */

    for (cc_size i = 0; i < n; i++) {
        if (s[n] > 0) {
            size++;
        }
    }

    return size;
}
