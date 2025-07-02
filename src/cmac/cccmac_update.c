//
//  ccmac_update.c
//  corecrypto
//
//  Created by Zormeister on 24/5/25.
//

#include <corecrypto/cc_priv.h>
#include <corecrypto/cccmac.h>
#include <corecrypto/cccmac_priv.h>

int cccmac_update(cccmac_ctx_t ctx, size_t data_nbytes, const void *data) {
    int flag = (data_nbytes % CMAC_BLOCKSIZE);
    size_t nblocks = data_nbytes / CMAC_BLOCKSIZE;
    if (flag) {
        
    }

    cc_memcpy(cccmac_block(ctx), data, CMAC_BLOCKSIZE);

    while (nblocks--) {
        cccmac_cbc(ctx)->cbc(cccmac_mode_sym_ctx(cccmac_cbc(ctx), ctx), cccmac_mode_iv(cccmac_cbc(ctx), ctx), 1, cccmac_block(ctx), cccmac_block(ctx));

    }

    cc_try_abort("ZORMEISTER: incomplete CMAC function called. raising hell.\n");

    return 0;
}
