//
//  ccblowfish_ltc_internal.h
//  corecrypto
//
//  Created by Zormeister on 12/5/2025.
//

#ifndef _CORECRYPTO_CCBLOWFISH_LTC_INTERNAL_H_
#define _CORECRYPTO_CCBLOWFISH_LTC_INTERNAL_H_

#include <corecrypto/ccblowfish.h>

// Thank you so much to Tom St Denis for the implementation for the Blowfish cipher
// LibTomCrypt is licensed under the unlicense.

extern const uint32_t ORIG_P[16 + 2];
extern const uint32_t ORIG_S[4][256];

struct ccblowfish_ltc_ctx {
    uint32_t S[4][256];
    uint32_t K[18];
};

extern const struct ccmode_ecb ccblowfish_ltc_ecb_encrypt_mode;
extern const struct ccmode_ecb ccblowfish_ltc_ecb_decrypt_mode;

#endif /* _CORECRYPTO_CCBLOWFISH_LTC_INTERNAL_H_ */
