//
//  ccmode_factory_xts.c
//  corecrypto
//
//  Created by Zormeister on 28/7/2025.
//

#include "corecrypto/ccmode.h"
#include <corecrypto/cc.h>
#include <corecrypto/cc_priv.h>
#include <corecrypto/ccmode_factory.h>
#include <corecrypto/ccmode_impl.h>

void ccmode_factory_xts_decrypt(struct ccmode_xts *xts, const struct ccmode_ecb *ecb, const struct ccmode_ecb *ecb_encrypt) {
    /* Fill in size parameters */
    xts->size = sizeof(struct _ccmode_xts_key);
    xts->block_size = ccecb_block_size(ecb);
    xts->tweak_size = sizeof(struct _ccmode_xts_tweak);

    /* Populate function callbacks */
    xts->init = ccmode_xts_init;
    xts->key_sched = ccmode_xts_key_sched;
    xts->set_tweak = ccmode_xts_set_tweak;
    xts->xts = ccmode_xts_crypt;

    /* Populate the custom fields */
    xts->custom = ecb;
    xts->custom1 = ecb_encrypt;
}

void ccmode_factory_xts_encrypt(struct ccmode_xts *xts, const struct ccmode_ecb *ecb, const struct ccmode_ecb *ecb_encrypt) {
    /* Fill in size parameters */
    xts->size = sizeof(struct _ccmode_xts_key);
    xts->block_size = ccecb_block_size(ecb);
    xts->tweak_size = sizeof(struct _ccmode_xts_tweak);

    /* Populate function callbacks */
    xts->init = ccmode_xts_init;
    xts->key_sched = ccmode_xts_key_sched;
    xts->set_tweak = ccmode_xts_set_tweak;
    xts->xts = ccmode_xts_crypt;

    /* Populate the custom fields */
    xts->custom = ecb;
    xts->custom1 = ecb_encrypt;
}
