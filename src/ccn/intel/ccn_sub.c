//
//  ccn_sub.c
//  corecrypto
//
//  Created by Zormeister on 16/6/2025.
//

#include <corecrypto/ccn.h>

#if CCN_SUB_ASM

#include <immintrin.h>

#if CCN_UNIT_SIZE == 8
#define cc_subborrow(bin, x, y, out) _subborrow_u64(bin, x, y, out)
#elif CCN_UNIT_SIZE == 4
#define cc_subborrow(bin, x, y, out) _subborrow_u32(bin, x, y, out)
#endif

cc_unit ccn_sub_asm(cc_size n, cc_unit *r, const cc_unit *s, const cc_unit *t)
{
    uint8_t borrow_in = 0;

    if (ccn_cmp(n, s, t) == -1) {
        return 1;
        /* ^ i believe this is what the comment at the header declaration meant */
    }

    for (cc_size i = 0; i < n; i++) {
        borrow_in = cc_subborrow(borrow_in, s[i], t[i], &r[i]);
    }

    return borrow_in;
}

#endif