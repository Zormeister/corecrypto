//
//  ccrng_pbkdf2_prng.c
//  corecrypto
//
//  Created by Zormeister on 29/7/2025.
//

#include <corecrypto/cc_priv.h>
#include <corecrypto/ccpbkdf2.h>
#include <corecrypto/ccrng_pbkdf2_prng.h>
#include <corecrypto/ccsha2.h>

static int ccrng_pbkdf2_prng_generate(struct ccrng_state *rng, size_t outlen, void *out)
{
    struct ccrng_pbkdf2_prng_state *state = (struct ccrng_pbkdf2_prng_state *)rng;

    if (outlen > state->buffer_size) {
        return CCERR_OVERFLOW;
    }

    /* Work from the end of the PRNG buffer... */
    size_t offset = state->buffer_size - outlen;

    cc_memcpy(out, (state->buffer + offset), outlen);

    /* I don't think we want to reuse any data in a PRNG. */
    state->buffer_size -= outlen;

    return CCERR_OK;
}

int ccrng_pbkdf2_prng_init(struct ccrng_pbkdf2_prng_state *state,
                           size_t max_output,
                           size_t password_length, const void *password,
                           size_t salt_length, const void *salt,
                           size_t iterations)
{
    if (max_output > 4096) {
        return CCERR_OVERFLOW;
    }

    /* populate the generate callback */
    state->generate = &ccrng_pbkdf2_prng_generate;

    ccpbkdf2_hmac(ccsha256_di(), password_length, password, salt_length, salt, iterations, max_output, state->buffer);

    return CCERR_OK;
}
