//
//  ccsha1_initial_state.c
//  corecrypto
//
//  Created by Zormeister on 29/7/2025.
//

#include "ccsha1_internal.h"

const uint32_t ccsha1_initial_state[5] = {
    0x67452301U,
    0xefcdab89U,
    0x98badcfeU,
    0x10325476U,
    0xc3d2e1f0U,
};
