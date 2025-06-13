//
//  ccmode_factory_ctr.c
//  corecrypto
//
//  Created by Zormeister on 13/5/2025.
//

#include <corecrypto/cc.h>
#include <corecrypto/cc_priv.h>
#include <corecrypto/ccmode_factory.h>
#include <corecrypto/ccn.h>

void ccmode_factory_ctr_crypt(struct ccmode_ctr *ctr, const struct ccmode_ecb *ecb) {
    ctr->size = ccn_sizeof_size(sizeof(struct _ccmode_ctr_key)) + 2 * ccn_sizeof_size(ecb->block_size) + ccn_sizeof_size(ecb->size);
    ctr->block_size = 1;
    ctr->ecb_block_size = ecb->block_size;
    ctr->init = ccmode_ctr_init;
    ctr->setctr = ccmode_ctr_setctr;
    ctr->ctr = ccmode_ctr_crypt;
}
