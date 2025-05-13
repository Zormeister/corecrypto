//
//  ccmode_factory_ctr.c
//  corecrypto
//
//  Created by Zormeister on 13/5/2025.
//

#include <corecrypto/cc.h>
#include <corecrypto/cc_abort.h>
#include <corecrypto/ccmode_factory.h>

void ccmode_factory_ctr_crypt(struct ccmode_ctr *ctr, const struct ccmode_ecb *ecb) {
    ctr->size = ccn_sizeof_size(sizeof(struct _ccmode_ctr_key)) + 2 * ccn_sizeof_size(ecb->block_size) + ccn_sizeof_size(ecb->size);
    ctr->block_size = 1;
    ctr->ecb_block_size = ecb->block_size;
    ctr->init = ccmode_ctr_init;
}

int ccmode_ctr_init(const struct ccmode_ctr *ctr, ccctr_ctx *ctx, size_t rawkey_len, const void *rawkey, const void *iv) {
    struct _ccmode_ctr_key *ckey = (struct _ccmode_ctr_key *)ctx;
    ckey->ecb = ctr->custom;
    cc_abort("=== CTR UNIMPLEMENTED ===");
    return 0;
}
