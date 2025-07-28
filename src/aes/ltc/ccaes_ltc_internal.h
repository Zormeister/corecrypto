//
//  ccaes_ltc_internal.h
//  corecrypto
//
//  Created by Zormeister on 28/7/2025.
//

#ifndef _CORECRYPTO_CCAES_LTC_INTERNAL_H_
#define _CORECRYPTO_CCAES_LTC_INTERNAL_H_

#include <corecrypto/ccaes.h>

typedef struct ltc_rijndael_key {
    uint32_t eK[60], dK[60];
    int Nr;
} ltc_rijndael_keysched;

extern int ccaes_ltc_init(const unsigned char *key, int keylen, int num_rounds, ccecb_ctx *skey);
extern int ccaes_ltc_ecb_encrypt(const unsigned char *pt, unsigned char *ct, ccecb_ctx *skey);
extern int ccaes_ltc_ecb_decrypt(const unsigned char *ct, unsigned char *pt, ccecb_ctx *skey);

#endif /* _CORECRYPTO_CCAES_LTC_INTERNAL_H_ */
