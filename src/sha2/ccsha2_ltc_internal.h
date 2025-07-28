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

extern void ccsha256_ltc_compress(ccdigest_state_t state, size_t nblocks, const void *data);

/* 
 * LTC SHA-2 TODO: SHA-384, SHA-512.
 *
 * I think due to the way some of the code is handled DarwinBoot's CCDxe won't link properly.
 *
 * eg: for some godforsaken reason the compiled library doesn't have:
 * - ccmd5_di
 * - ccsha384_di
 * - ccsha512_di
 *
 * I thought we already had SHA-384?
 * Unless the selector code hasn't been implemented yet, I'll get around to it.
 *
 * There's a high chance I'll end up re-working the implementations anyways, mostly just to match the SHA
 * implementations with one another to avoid a weird scenario.
 */

#endif
