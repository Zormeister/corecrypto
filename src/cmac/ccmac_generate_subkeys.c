//
//  ccmac_generate_subkeys.c
//  corecrypto
//
//  Created by Zormeister on 12/4/25.
//

#include <corecrypto/cccmac_priv.h>
#include <corecrypto/ccmode.h>

int cccmac_generate_subkeys(cccmac_ctx_t ctx, size_t key_nbytes, const void *key, uint8_t *key1, uint8_t *key2) {
    uint8_t iv[16] = {0};
    uint8_t buf[16] = {0};

    int ret = cccbc_one_shot(cccmac_cbc(ctx), key_nbytes, key, iv, 1, buf, buf);
    if (ret) { return ret; }
    
    return CCERR_OK;
}
