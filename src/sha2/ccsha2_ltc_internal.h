//
//  ccsha2_ltc_internal.h
//  corecrypto
//
//  Created by Zormeister on 27/5/2025.
//

#ifndef _CORECRYPTO_CCSHA2_LTC_INTERNAL_H_
#define _CORECRYPTO_CCSHA2_LTC_INTERNAL_H_

#include <corecrypto/ccsha2.h>

extern const uint32_t ccsha224_initial_state[8];
extern const uint32_t ccsha256_initial_state[8];
extern const uint32_t ccsha384_initial_state[8];
extern const uint32_t ccsha512_initial_state[8];

extern const uint32_t ccsha256_K[64];

extern void ccsha256_ltc_compress(ccdigest_state_t state, unsigned long nblocks, const void *data);

#endif
