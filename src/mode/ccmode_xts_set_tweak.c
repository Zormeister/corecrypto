//
//  ccmode_xts_set_tweak.c
//  corecrypto
//
//  Created by Zormeister on 28/7/2025.
//

#include "ccmode_internal.h"
#include <corecrypto/ccmode.h>
#include <corecrypto/ccmode_factory.h>

/* set the tweak (encrypt it to prep it for usage) */
int ccmode_xts_set_tweak(const ccxts_ctx *ctx, ccxts_tweak *tweak, const void *iv)
{
    struct _ccmode_xts_key *key = (struct _ccmode_xts_key *)ctx;
    struct _ccmode_xts_tweak *twk = (struct _ccmode_xts_tweak *)tweak;

    /* this is (hopefully) a new tweak */
    twk->blocks_processed = 0;

    /* encrypt the IV to create the tweak */
    ccecb_update(key->ecb_encrypt, CCMODE_XTS_KEY_ECB_ENCRYPT_CTX(key), 1, iv, &twk->u);

    return CCERR_OK;
}
