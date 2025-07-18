//
//  ccdes_ltc_desfunc.c
//  corecrypto
//
//  Created by Zormeister on 10/5/2025.
//

#include "ccdes_ltc_internal.h"
#include <corecrypto/cc_config.h>
#include <corecrypto/cc_priv.h>
#include <corecrypto/ccdes.h>
#include <corecrypto/ccn.h>

// Thank you so much to Tom St Denis for the implementation for DES and Triple-DES
// LibTomCrypt is licensed under the unlicense.

void desfunc(uint32_t *block, const uint32_t *keys)
{
    uint32_t work, right, leftt;
    int cur_round;

    leftt = block[0];
    right = block[1];

    work = ((leftt >> 4) ^ right) & 0x0f0f0f0fL;
    right ^= work;
    leftt ^= (work << 4);

    work = ((leftt >> 16) ^ right) & 0x0000ffffL;
    right ^= work;
    leftt ^= (work << 16);

    work = ((right >> 2) ^ leftt) & 0x33333333L;
    leftt ^= work;
    right ^= (work << 2);

    work = ((right >> 8) ^ leftt) & 0x00ff00ffL;
    leftt ^= work;
    right ^= (work << 8);

    right = CC_ROLc(right, 1);
    work = (leftt ^ right) & 0xaaaaaaaaL;

    leftt ^= work;
    right ^= work;
    leftt = CC_ROLc(leftt, 1);

    for (cur_round = 0; cur_round < 8; cur_round++) {
        work = CC_RORc(right, 4) ^ *keys++;
        leftt ^= SP7[work & 0x3fL]
            ^ SP5[(work >> 8) & 0x3fL]
            ^ SP3[(work >> 16) & 0x3fL]
            ^ SP1[(work >> 24) & 0x3fL];
        work = right ^ *keys++;
        leftt ^= SP8[work & 0x3fL]
            ^ SP6[(work >> 8) & 0x3fL]
            ^ SP4[(work >> 16) & 0x3fL]
            ^ SP2[(work >> 24) & 0x3fL];

        work = CC_RORc(leftt, 4) ^ *keys++;
        right ^= SP7[work & 0x3fL]
            ^ SP5[(work >> 8) & 0x3fL]
            ^ SP3[(work >> 16) & 0x3fL]
            ^ SP1[(work >> 24) & 0x3fL];
        work = leftt ^ *keys++;
        right ^= SP8[work & 0x3fL]
            ^ SP6[(work >> 8) & 0x3fL]
            ^ SP4[(work >> 16) & 0x3fL]
            ^ SP2[(work >> 24) & 0x3fL];
    }

    right = CC_RORc(right, 1);
    work = (leftt ^ right) & 0xaaaaaaaaL;
    leftt ^= work;
    right ^= work;
    leftt = CC_RORc(leftt, 1);
    work = ((leftt >> 8) ^ right) & 0x00ff00ffL;
    right ^= work;
    leftt ^= (work << 8);
    /* -- */
    work = ((leftt >> 2) ^ right) & 0x33333333L;
    right ^= work;
    leftt ^= (work << 2);
    work = ((right >> 16) ^ leftt) & 0x0000ffffL;
    leftt ^= work;
    right ^= (work << 16);
    work = ((right >> 4) ^ leftt) & 0x0f0f0f0fL;
    leftt ^= work;
    right ^= (work << 4);

    block[0] = right;
    block[1] = leftt;
}
