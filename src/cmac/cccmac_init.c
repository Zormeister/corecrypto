//
//  ccmac_init.c
//  corecrypto
//
//  Created by Zormeister on 13/4/25.
//

#include <corecrypto/cc_priv.h>
#include <corecrypto/cccmac_priv.h>

int cccmac_init(const struct ccmode_cbc *cbc, cccmac_ctx_t ctx, size_t key_nbytes, const void *key) {
    cccmac_cbc(ctx) = cbc;

    /* Block size CANNOT be larger than CMAC_BLOCKSIZE. */
    if (cbc->block_size > CMAC_BLOCKSIZE) {
        return CCERR_PARAMETER;
    }

    cccmac_generate_subkeys(cbc, key_nbytes, key, cccmac_k1(ctx), cccmac_k2(ctx));

    /* Anything else? */
    return CCERR_OK;
}
