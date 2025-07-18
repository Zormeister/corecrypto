//
//  ccrc2_ltc_ecb_encrypt_mode.c
//  corecrypto
//
//  Created by Zormeister on 2/6/2025.
//

#include "ccrc2_ltc_internal.h"
#include <corecrypto/ccn.h>

const struct ccmode_ecb ccrc2_ltc_ecb_encrypt_mode = {
    .size = ccn_nof_sizeof(struct ccrc2_ltc_ctx),
    .block_size = CCRC2_BLOCK_SIZE,
    .init = ccrc2_ltc_setup,
    .ecb = ccrc2_ltc_ecb_encrypt,
};
