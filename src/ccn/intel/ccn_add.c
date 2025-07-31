//
//  ccn_add.c
//  corecrypto
//
//  Created by Zormeister on 15/6/2025.
//

#include <corecrypto/ccn.h>

#if 0

#if CCN_ADD_ASM

#include <immintrin.h>

#if CCN_UNIT_SIZE == 8
#define cc_addcarry(cin, a, b, out) _addcarry_u64(cin, a, b, out)
#elif CCN_UNIT_SIZE == 4
#define cc_addcarry(cin, a, b, out) _addcarry_u32(cin, a, b, out)
#endif

cc_unit ccn_add_asm(cc_size n, cc_unit *r, const cc_unit *s, const cc_unit *t)
{
    uint8_t carry_in = 0;
    cc_unit carry = 0;

    for (cc_size i = 0; i < n; i++) {
        carry_in = cc_addcarry(carry_in, s[i], t[i], &r[i]);
    }

    if (carry_in) {
        /* ^ we have spilled over r, thus we must return the value of the carry */
        cc_addcarry(carry_in, 0, 0, &carry);
        return carry;
    }

    return 0;
}

#endif

#endif
