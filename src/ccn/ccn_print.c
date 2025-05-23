//
//  ccn_print.c
//  corecrypto
//
//  Created by Zormeister on 22/5/2025.
//

#include <stdio.h>
#include <corecrypto/ccn.h>

void ccn_print(cc_size n, const cc_unit *s) {
    while (n--) {
#if CCN_UNIT_SIZE == 8
        printf("%.016lx", s[n]);
#elif CCN_UNIT_SIZE == 4
        printf("%.08x", s[n]);
#elif CCN_UNIT_SIZE == 2
        printf("%.04x", s[n]);
#elif CCN_UNIT_SIZE == 1
        printf("%.02x", s[n]);
#endif
    }
}

void ccn_lprint(cc_size n, const char *label, const cc_unit *s) {
    /* print ts to stdout */
    printf("%s { %zu, ", label, n);

    while (n--) {
#if CCN_UNIT_SIZE == 8
        printf("%.016lx", s[n]);
#elif CCN_UNIT_SIZE == 4
        printf("%.08x", s[n]);
#elif CCN_UNIT_SIZE == 2
        printf("%.04x", s[n]);
#elif CCN_UNIT_SIZE == 1
        printf("%.02x", s[n]);
#endif
    }
    printf("}\n");
}
