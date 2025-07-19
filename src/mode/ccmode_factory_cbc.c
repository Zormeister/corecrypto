//
//  ccmode_factory_cbc.c
//  corecrypto
//
//  Created by Zormeister on 9/5/2025.
//

#include <corecrypto/cc.h>
#include <corecrypto/cc_priv.h>
#include <corecrypto/ccmode_factory.h>
#include <corecrypto/ccmode_impl.h>

/* These functions are essentially act as wrappers so every implementation doesn't need to repeat the same code. */

void ccmode_factory_cbc_encrypt(struct ccmode_cbc *cbc, const struct ccmode_ecb *ecb)
{
    /* construct a cbc mode from an ecb mode. */

    cbc->block_size = ecb->block_size;                                                                                           /* equal block sizes */
    cbc->custom = ecb;                                                                                                           /* this is how we get the selected ecb mode to the context in init */
    cbc->size = ccn_sizeof_size(sizeof(struct _ccmode_cbc_key)) + ccn_sizeof_size(ecb->block_size) + ccn_sizeof_size(ecb->size); /* take into account that the context size could be different across */

    cbc->init = ccmode_cbc_init;
    cbc->cbc = ccmode_cbc_encrypt;
}

void ccmode_factory_cbc_decrypt(struct ccmode_cbc *cbc, const struct ccmode_ecb *ecb)
{
    /* construct a cbc mode from an ecb mode. */

    cbc->block_size = ecb->block_size;                                                                                           /* equal block sizes */
    cbc->custom = ecb;                                                                                                           /* this is how we get the selected ecb mode to the context in init */
    cbc->size = ccn_sizeof_size(sizeof(struct _ccmode_cbc_key)) + ccn_sizeof_size(ecb->block_size) + ccn_sizeof_size(ecb->size); /* take into account that the context size could be different across */

    cbc->init = ccmode_cbc_init;
    cbc->cbc = ccmode_cbc_decrypt;
}
