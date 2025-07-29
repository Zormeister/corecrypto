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
extern const uint64_t ccsha384_initial_state[8];
extern const uint64_t ccsha512_initial_state[8];
extern const uint64_t ccsha512_224_initial_state[8];
extern const uint64_t ccsha512_256_initial_state[8];

extern const uint32_t ccsha256_K[64];
extern const uint64_t ccsha512_K[80];

extern void ccsha256_ltc_compress(ccdigest_state_t state, size_t nblocks, const void *data);
extern void ccsha512_ltc_compress(ccdigest_state_t state, size_t nblocks, const void *data);
extern void ccsha512_final(const struct ccdigest_info *di, ccdigest_ctx_t ctx, void *digest);

#endif
