//  adapted from botan/src/lib/rng/rdrnd_rng/rdrand_rng.cpp
//  Botan  http://botan.randombit.net
//  License :  https://github.com/randombit/botan/blob/master/doc/license.txt

#include <corecrypto/cckprng.h>

int cckprng_init(cckprng_ctx_t ctx, size_t nbytes, const void *seed) {
	// Nothing to do here, rdrand cannot be seeded.
	return CCKPRNG_OK;
}

int cckprng_reseed(cckprng_ctx_t ctx, size_t nbytes, const void *seed) {
	// Nothing to do here, rdrand cannot be seeded.
	return CCKPRNG_OK;
}

int cckprng_addentropy(cckprng_ctx_t ctx, size_t nbytes, const void *seed) {
	// Nothing to do here, rdrand cannot be seeded.
	return CCKPRNG_OK;
}

// MARK: -

static int rdrand(uint64_t *value) {
	if (value == NULL) return CCKPRNG_ABORT;

	// According to Intel, RDRAND is guaranteed to generate a random
	// number within 10 retries on a working CPU.
	const size_t retries = 10;
	for (size_t i = 0; i < retries; i++) {
		uint64_t output = 0;
		int cf = 0;

		asm("rdrand %0; adcl $0, %1" : "=r" (output), "=r" (cf) : "0" (output), "1" (cf) : "cc");

		if (cf == 1) {
			*value = output;
			return CCKPRNG_OK;
		}
	}

	return CCKPRNG_ABORT;
}

int cckprng_generate(cckprng_ctx_t ctx, size_t nbytes, void *out) {
	uint64_t random = 0;
	uint8_t *buffer = (uint8_t *)out;

	for (size_t i = 0; i < nbytes; i++) {
		int mod4 = i % 4;
		if (mod4 == 0) {
			int error = rdrand(&random);
			if (error != CCKPRNG_OK) return error;
		}

		uint8_t byte;
		if (mod4 == 0) byte = random & 0xFF;
		else if (mod4 == 1) byte = (random >> 8) & 0xFF;
		else if (mod4 == 2) byte = (random >> 16) & 0xFF;
		else if (mod4 == 3) byte = (random >> 24) & 0xFF;
		else return CCKPRNG_ABORT;

		buffer[i] = byte;
	}

	return CCKPRNG_OK;
}
