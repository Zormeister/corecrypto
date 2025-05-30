//
//  ccsha256_ltc_di.c
//  corecrypto
//
//  Created by Zormeister on 27/5/2025.
//

#include "ccsha2_ltc_internal.h"
#include <corecrypto/ccsha2.h>
#include <corecrypto/ccdigest_priv.h>

const struct ccdigest_info ccsha256_ltc_di = {
    .block_size = CCSHA256_BLOCK_SIZE,
    .output_size = CCSHA256_OUTPUT_SIZE,
    .state_size = CCSHA256_STATE_SIZE,

    .final = ccdigest_final_64be,
    .compress = ccsha256_ltc_compress,

    .initial_state = ccsha256_initial_state,

    .oid = ccoid_sha256,
    .oid_size = ccoid_sha256_len,
};

