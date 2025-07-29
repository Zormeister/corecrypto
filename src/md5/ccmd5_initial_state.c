//
//  ccmd5_initial_state.c
//  corecrypto
//
//  Created by Zormeister on 29/7/2025.
//

#include "ccmd5_internal.h"

const uint32_t ccmd5_initial_state[4] = {
    0x67452301UL,
    0xefcdab89UL,
    0x98badcfeUL,
    0x10325476UL
};
