//
//  ccsha512_224_ltc_di.c
//  corecrypto
//
//  Created by Zormeister on 29/7/2025.
//

#include "ccsha2_ltc_internal.h"
#include <corecrypto/ccdigest_priv.h>
#include <corecrypto/ccsha2.h>

const struct ccdigest_info ccsha512_224_ltc_di = {
    .output_size = CCSHA512_224_OUTPUT_SIZE,
    .state_size = CCSHA512_224_STATE_SIZE,
    .block_size = CCSHA512_224_BLOCK_SIZE,

    .oid_size = ccoid_sha512_224_len,
    .oid = CC_DIGEST_OID_SHA512_224,

    .initial_state = ccsha512_224_initial_state,

    .compress = ccsha512_ltc_compress,
    .final = ccsha512_final,
};
