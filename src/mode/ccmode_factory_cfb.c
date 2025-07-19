//
//  ccmode_factory_cfb.c
//  corecrypto
//
//  Created by Zormeister on 31/5/2025.
//

#include <corecrypto/cc.h>
#include <corecrypto/cc_priv.h>
#include <corecrypto/ccmode_factory.h>

void ccmode_factory_cfb_encrypt(struct ccmode_cfb *cfb, const struct ccmode_ecb *ecb)
{
    cfb->size       = ccn_sizeof_size(sizeof(struct _ccmode_cfb_key)) + 2 * ccn_sizeof_size((ecb)->block_size) + ccn_sizeof_size((ecb)->size);
    cfb->block_size = 1;
    cfb->init       = ccmode_cfb_init;
    cfb->cfb        = ccmode_cfb_encrypt;
    cfb->custom     = ecb;
}

void ccmode_factory_cfb_decrypt(struct ccmode_cfb *cfb, const struct ccmode_ecb *ecb)
{
    cfb->size       = ccn_sizeof_size(sizeof(struct _ccmode_cfb_key)) + 2 * ccn_sizeof_size((ecb)->block_size) + ccn_sizeof_size((ecb)->size);
    cfb->block_size = 1;
    cfb->init       = ccmode_cfb_init;
    cfb->cfb        = ccmode_cfb_decrypt;
    cfb->custom     = ecb;
}
