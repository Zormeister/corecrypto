//
//  ccmode_xts_init.c
//  corecrypto
//
//  Created by Zormeister on 28/7/2025.
//

#include "corecrypto/cc.h"
#include <corecrypto/ccmode_factory.h>

int ccmode_xts_init(const struct ccmode_xts *xts, ccxts_ctx *ctx, size_t key_nbytes, const void *data_key, const void *tweak_key) {
    struct _ccmode_xts_key *key = (struct _ccmode_xts_key *)ctx;

    /* for sanity's sake, let us ensure that data_key and tweak_key are different */
    if (!cc_cmp_safe(key_nbytes, data_key, tweak_key)) {
    
    }

    /* set the ECB modes for usage in ccmode_xts_set_tweak + ccmode_xts_crypt */
    key->ecb = xts->custom;
    key->ecb_encrypt = xts->custom1;

    ccmode_xts_key_sched(xts, ctx, key_nbytes, data_key, tweak_key);
    return CCERR_OK;
}
