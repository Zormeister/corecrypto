#include <corecrypto/cckprng.h>
#include "yarrow/yarrow.h"

void cckprng_init(struct cckprng_ctx *ctx, unsigned max_ngens, size_t entropybuf_nbytes, const void *entropybuf,
				  const uint32_t *entropybuf_nsamples, size_t seed_nbytes, const void *seed, size_t nonce_nbytes,
				  const void *nonce) {
	prngInitialize(&ctx->prng);
	ctx->bytes_generated = ctx->bytes_since_entropy = 0;

	cckprng_reseed(ctx, seed_nbytes, seed);
}

void cckprng_initgen(struct cckprng_ctx *ctx, unsigned gen_idx) {
	// Nothing is needed here.
}

void cckprng_reseed(struct cckprng_ctx *ctx, size_t nbytes, const void *seed) {
	prngInput(ctx->prng, (BYTE *)seed, (UINT)nbytes, 0, 0);
	prngAllowReseed(ctx->prng, 5000);
	ctx->bytes_since_entropy = 0;
}

void cckprng_refresh(struct cckprng_ctx *ctx) {
	// Nothing is needed here, either.
}

void cckprng_generate(struct cckprng_ctx *ctx, unsigned gen_idx, size_t nbytes, void *out) {
	BYTE *buffer = (BYTE *)out;
	while (nbytes > UINT32_MAX) {
		prngOutput(ctx->prng, buffer, UINT32_MAX);
		ctx->bytes_generated += UINT32_MAX;
		ctx->bytes_since_entropy += UINT32_MAX;

		buffer += UINT32_MAX;
		nbytes -= UINT32_MAX;
		nbytes = CC_MAX(nbytes, 0);
	}

	if (nbytes != 0) {
		prngOutput(ctx->prng, buffer, (UINT)nbytes);
		ctx->bytes_generated += nbytes;
		ctx->bytes_since_entropy += nbytes;
	}
}
