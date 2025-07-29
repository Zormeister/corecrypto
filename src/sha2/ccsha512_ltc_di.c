//
//  ccsha512_ltc_di.c
//  corecrypto
//
//  Created by Zormeister on 29/7/2025.
//

#include "ccsha2_ltc_internal.h"
#include <corecrypto/ccdigest_priv.h>
#include <corecrypto/ccsha2.h>

const struct ccdigest_info ccsha512_ltc_di = {
    .block_size = CCSHA512_BLOCK_SIZE,
    .output_size = CCSHA512_OUTPUT_SIZE,
    .state_size = CCSHA512_STATE_SIZE,

    .final = ccsha512_final,
    .compress = ccsha512_ltc_compress,

    .initial_state = ccsha256_initial_state,

    .oid = ccoid_sha512,
    .oid_size = ccoid_sha512_len,
};
