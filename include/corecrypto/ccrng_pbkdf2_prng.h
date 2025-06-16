//
//  ccrng_pbkd2_prng.h
//  corecrypto
//
//  Created by Zormeister on 17/6/25.
//

#ifndef _CORECRYPTO_CCRNG_PBKDF2_PRNG_H_
#define _CORECRYPTO_CCRNG_PBKDF2_PRNG_H_

#include <corecrypto/ccrng.h>

/* This doesn't even have to be compatible structure-layout wise. just has to work as intended. */
struct ccrng_pbkd2_prng_state {
    CCRNG_STATE_COMMON

    const void *password;
    size_t password_length;
    size_t iterations;
    const void *salt;
    size_t salt_length;
    size_t output_size;
};

int ccrng_pbkdf2_prng_init(struct ccrng_pbkd2_prng_state *state,
                          size_t max_output,
                          size_t password_length, const void *password,
                          size_t salt_length, const void *salt,
                          size_t iterations);

/* Does this even have a specification? or does this just run a PBKDF2 HMAC operation? */

#endif /* _CORECRYPTO_CCRNG_PBKDF2_PRNG_H_ */
