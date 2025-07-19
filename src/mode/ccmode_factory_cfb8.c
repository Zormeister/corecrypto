//
//  ccmode_factory_cfb8.c
//  corecrypto
//
//  Created by Zormeister on 14/6/2025.
//

#include "corecrypto/ccmode_factory.h"
#include <corecrypto/cc_priv.h>

void ccmode_factory_cfb8_decrypt(struct ccmode_cfb8 *cfb8, const struct ccmode_ecb *ecb)
{
    cfb8->size = ccn_sizeof_size(sizeof(struct _ccmode_cfb8_key)) + 2 * ccn_sizeof_size(ecb->block_size) + ccn_sizeof_size(ecb->size);
    cfb8->block_size = 1;
    cfb8->init = ccmode_cfb8_init;
    cfb8->cfb8 = ccmode_cfb8_decrypt;
    cfb8->custom = ecb;
}

void ccmode_factory_cfb8_encrypt(struct ccmode_cfb8 *cfb8, const struct ccmode_ecb *ecb)
{
    cfb8->size = ccn_sizeof_size(sizeof(struct _ccmode_cfb8_key)) + 2 * ccn_sizeof_size(ecb->block_size) + ccn_sizeof_size(ecb->size);
    cfb8->block_size = 1;
    cfb8->init = ccmode_cfb8_init;
    cfb8->cfb8 = ccmode_cfb8_encrypt;
    cfb8->custom = ecb;
}
