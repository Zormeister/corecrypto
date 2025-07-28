//
//  ccprime.h
//  corecrypto
//
//  Created by Zormeister on 28/7/2025.
//

#ifndef _CORECRYPTO_CCPRIME_H_
#define _CORECRYPTO_CCPRIME_H_

#include <corecrypto/ccrng.h>
#include <corecrypto/ccn.h>
#include <corecrypto/cczp.h>

/* so, CoreCrypto has a bunch of Prime Number related routines */

/*
 0000000000056c88 t _ccprime_generate
 0000000000042a6d t _ccprime_rabin_miller
 000000000004286e t _ccprime_sieve
 */

/*
 * And I've done some probing for this function signature.
 *
 * Alongside referencing other functions (RSA and EC) signatures for guidance
 */

/* I honestly have no idea what these do. */
int ccprime_generate(cc_size nbits,
                     cczp_t zp,
                     cc_unit *unk, /* ??? */
                     struct ccrng_state *rng,
                     struct ccrng_state *rng2);

#endif /* _CORECRYPTO_CCPRIME_H_ */
