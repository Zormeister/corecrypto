//
//  ccrc2_ltc_internal.h
//  corecrypto
//
//  Created by Zormeister on 2/6/2025.
//

#ifndef _CORECRYPTO_CCRC2_LTC_INTERNAL_H_
#define _CORECRYPTO_CCRC2_LTC_INTERNAL_H_

#include <corecrypto/ccrc2.h>

struct ccrc2_ltc_ctx {
    uint32_t xkey[64];
};

int ccrc2_ltc_setup(const struct ccmode_ecb *ecb, ccecb_ctx *ctx, size_t key_nbytes, const void *key);

int ccrc2_ltc_ecb_decrypt(const ccecb_ctx *ctx, size_t nblocks, const void *in, void *out);

int ccrc2_ltc_ecb_encrypt(const ccecb_ctx *ctx, size_t nblocks, const void *in, void *out);

#endif /* _CORECRYPTO_CCRC2_LTC_INTERNAL_H_ */