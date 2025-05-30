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
    /* Our subkeys should've been generated in the cccmac_init stage */
    size_t rounds = (data_nbytes + 15) / 16;
    return 0;
}
