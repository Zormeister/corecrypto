//
//  ccmode_ctr_setctr.c
//  corecrypto
//
//  Created by Zormeister on 13/6/2025.
//

#include "ccmode_internal.h"
#include <corecrypto/cc_priv.h>

int ccmode_ctr_setctr(const struct ccmode_ctr *mode, ccctr_ctx *ctx, const void *ctr)
{
    struct _ccmode_ctr_key *ckey = (struct _ccmode_ctr_key *)ctx;
    cc_memcpy(CCMODE_CTR_KEY_COUNTER(ckey), ctr, ckey->ecb->block_size); /* This gets a bit absurd for AES,  */
    return CCERR_OK;
}
