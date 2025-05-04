//
//  ccmac_generate_subkeys.c
//  corecrypto
//
//  Created by Zormeister on 12/4/25.
//

#include <corecrypto/cccmac_priv.h>

int cccmac_generate_subkeys(cccmac_ctx_t ctx, size_t key_nbytes, const void *key) {
    uint8_t buf[16];
    cccmac_cbc(ctx)->init(cccmac_cbc(ctx), cccmac_mode_ctx_start(cccmac_cbc(ctx), ctx), key_nbytes, key);
    //cccmac_cbc(ctx)->cbc(cccmac_mode_ctx_start(cccmac_cbc(ctx), ctx), 1, buf, buf);
}
