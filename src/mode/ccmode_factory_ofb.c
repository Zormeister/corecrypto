//
//  ccmode_factory_ofb.c
//  corecrypto
//
//  Created by Zormeister on 30/5/2025.
//

#include <corecrypto/cc.h>
#include <corecrypto/cc_priv.h>
#include <corecrypto/ccmode_factory.h>

void ccmode_factory_ofb_crypt(struct ccmode_ofb *ofb, const struct ccmode_ecb *ecb)
{
    ofb->size = ccn_sizeof_size(sizeof(struct _ccmode_ofb_key)) + ccn_sizeof_size(ecb->block_size) + ccn_sizeof_size(ecb->size);
    ofb->block_size = 1;
    ofb->init = ccmode_ofb_init;
    ofb->ofb = ccmode_ofb_crypt;
    ofb->custom = ecb;
}
