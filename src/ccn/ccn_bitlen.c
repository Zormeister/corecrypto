//
//  ccn_bitlen.c
//  corecrypto
//
//  Created by Zormeister on 30/7/2025.
//

#include <corecrypto/ccn.h>
#include <corecrypto/cc_priv.h>

cc_size ccn_bitlen(cc_size n, const cc_unit *s)
{
    cc_size avail = ccn_n(n, s);
    cc_size size = ccn_bitsof_n(avail);

    cc_unit u = s[avail - 1];

#if CCN_UNIT_SIZE == 8
    size -= cc_clz64(u);
#else
    size -= cc_clz32(ccn32_32_parse(s, avail - 1));
#endif

    return size;
}
