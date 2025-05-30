//
//  ccsha256_initial_state.c
//  corecrypto
//
//  Created by Zormeister on 27/5/2025.
//

#include "ccsha2_ltc_internal.h"

const uint32_t ccsha256_initial_state[8] = {
    0x6A09E667UL,
    0xBB67AE85UL,
    0x3C6EF372UL,
    0xA54FF53AUL,
    0x510E527FUL,
    0x9B05688CUL,
    0x1F83D9ABUL,
    0x5BE0CD19UL,
};
