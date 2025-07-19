//
//  ccn_print.c
//  corecrypto
//
//  Created by Zormeister on 22/5/2025.
//

#include <corecrypto/cc_debug.h>
#include <corecrypto/ccn.h>

void ccn_print(cc_size n, const cc_unit *s)
{
    while (n--) {
        cc_printf("%" CCPRIx_UNIT, s[n]);
    }
}

void ccn_lprint(cc_size n, const char *label, const cc_unit *s)
{
    /* print ts to stdout */
    printf("%s { %zu, ", label, n);

    while (n--) {
        cc_printf("%" CCPRIx_UNIT, s[n]);
    }
    printf("}\n");
}
