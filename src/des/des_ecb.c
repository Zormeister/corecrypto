//
//  des-ecb.c
//  corecrypto
//
//  Created by Zormeister on 26/1/2025.
//

#include <corecrypto/ccdes.h>
#include <corecrypto/cc_priv.h>

// Triple DES.
const struct ccmode_ecb des3_ltc_ecb_encrypt_mode = {
    .size = 0, // IDK yet
    .block_size = CCDES_BLOCK_SIZE, // 64bits
};
