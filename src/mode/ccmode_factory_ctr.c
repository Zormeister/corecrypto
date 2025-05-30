//
//  ccmode_factory_ctr.c
//  corecrypto
//
//  Created by Zormeister on 13/5/2025.
//

#include <corecrypto/cc.h>
#include <corecrypto/cc_priv.h>
#include <corecrypto/ccmode_factory.h>

#define CCMODE_CTR_COUNTER(ckey) ckey->u
#define CCMODE_CTR_ECB_CTX(ckey) (ccecb_ctx *)(ckey->u + ccn_sizeof_size(ckey->ecb->block_size) * 2)

void ccmode_factory_ctr_crypt(struct ccmode_ctr *ctr, const struct ccmode_ecb *ecb) {
    ctr->size = ccn_sizeof_size(sizeof(struct _ccmode_ctr_key)) + 2 * ccn_sizeof_size(ecb->block_size) + ccn_sizeof_size(ecb->size);
    ctr->block_size = 1;
    ctr->ecb_block_size = ecb->block_size;
    ctr->init = ccmode_ctr_init;
    ctr->setctr = ccmode_ctr_setctr;
    ctr->ctr = ccmode_ctr_crypt;
}

int ccmode_ctr_init(const struct ccmode_ctr *ctr, ccctr_ctx *ctx, size_t rawkey_len, const void *rawkey, const void *iv) {
    struct _ccmode_ctr_key *ckey = (struct _ccmode_ctr_key *)ctx;
    ckey->ecb = ctr->custom;
    ckey->ecb->init(ckey->ecb, CCMODE_CTR_ECB_CTX(ckey), rawkey_len, rawkey);
    return 0;
}

int ccmode_ctr_setctr(const struct ccmode_ctr *mode, ccctr_ctx *ctx, const void *ctr) {
    struct _ccmode_ctr_key *ckey = (struct _ccmode_ctr_key *)ctx;
    cc_memcpy(CCMODE_CTR_COUNTER(ckey), ctr, ckey->ecb->block_size);
    return CCERR_OK;
}
