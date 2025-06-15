//
//  ccn_cmp.c
//  corecrypto
//
//  Created by Zormeister on 16/6/2025.
//

#include <corecrypto/ccn.h>

int ccn_cmp(cc_size n, const cc_unit *s, const cc_unit *t) {
    if (n) {
        for (cc_size i = 0; i < n; i++) {
            if (s[i] > t[i]) {
                return 1;
            } else if (s[i] < t[i]) {
                return -1;
            }
        }
    }

    return 0;
}
