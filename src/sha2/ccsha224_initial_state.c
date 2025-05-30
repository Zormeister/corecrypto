//
//  ccsha224_initial_state.c
//  corecrypto
//
//  Created by Zormeister on 27/5/2025.
//

#include "ccsha2_ltc_internal.h"

const uint32_t ccsha224_initial_state[8] = {
    0xc1059ed8UL,
    0x367CD507UL,
    0x3070dd17UL,
    0xf70e5939UL,
    0xffc00b31UL,
    0x68581511UL,
    0x64f98fa7UL,
    0xbefa4fa4UL,
};
