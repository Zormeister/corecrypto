
#ifndef _CORECRYPTO_CCDES_LTC_INTERNAL_H_
#define _CORECRYPTO_CCDES_LTC_INTERNAL_H_

#include <corecrypto/ccdes.h>

// Thank you so much to Tom St Denis for the implementation for DES and Triple-DES
// LibTomCrypt is licensed under the unlicense.

#define EN0 0
#define DE1 1

/* constants */
extern const uint8_t pc1[56];
extern const uint8_t pc2[48];
extern const uint8_t totrot[16];
extern const uint32_t bytebit[8];
extern const uint32_t bigbyte[24];
extern const uint32_t SP1[64];
extern const uint32_t SP2[64];
extern const uint32_t SP3[64];
extern const uint32_t SP4[64];
extern const uint32_t SP5[64];
extern const uint32_t SP6[64];
extern const uint32_t SP7[64];
extern const uint32_t SP8[64];

extern void desfunc(uint32_t *block, const uint32_t *keys);
extern void deskey(const unsigned char *key, short edf, uint32_t *keyout);

struct ccdes_ltc_ecb_ctx {
    uint32_t ek[32];
    uint32_t dk[32];
};

struct ccdes3_ltc_ecb_ctx {
    uint32_t ek[3][32];
    uint32_t dk[3][32];
};

#endif /* _CORECRYPTO_CCDES_LTC_INTERNAL_H_ */
