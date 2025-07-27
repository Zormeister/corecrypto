//
//  ccmode_xts_keysched.c
//  corecrypto
//
//  Created by Zormeister on 28/7/2025.
//

#include "ccmode_internal.h"
#include <corecrypto/ccmode_factory.h>

/* set the key schedule here. */
void ccmode_xts_key_sched(const struct ccmode_xts *xts, ccxts_ctx *ctx, size_t key_nbytes, const void *data_key, const void *tweak_key)
{
    struct _ccmode_xts_key *key = (struct _ccmode_xts_key *)ctx;

    /* init the enc/dec mode and its key here */
    ccecb_init(key->ecb, CCMODE_XTS_KEY_ECB_CTX(key), key_nbytes, data_key);

    /* init the tweak encryptor mode - yes, the tweak gets encrypted prior to usage. */
    ccecb_init(key->ecb_encrypt, CCMODE_XTS_KEY_ECB_ENCRYPT_CTX(key), key_nbytes, tweak_key);
}
