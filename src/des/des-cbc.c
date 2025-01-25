//
//  des-cbc.c
//  corecrypto
//
//  Created by Zormeister on 25/1/2025.
//

#include <corecrypto/ccdes.h>

struct ccmode_cbc des_cbc_encrypt = {
    .block_size = CCDES_BLOCK_SIZE,
};
