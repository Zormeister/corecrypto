#include "cckprng.h"
#include "yarrow/yarrow.h"

int cckprng_init(cckprng_ctx_t ctx, size_t nbytes, const void *seed) {
	prngInitialize(&ctx->prng);
	ctx->bytes_generated = ctx->bytes_since_entropy = 0;

	return cckprng_reseed(ctx, nbytes, seed);
}

int cckprng_reseed(cckprng_ctx_t ctx, size_t nbytes, const void *seed) {
	prngInput(ctx->prng, (BYTE *)seed, (UINT)nbytes, 0, 0);
	prngAllowReseed(ctx->prng, 5000);
	ctx->bytes_since_entropy = 0;
	return CCKPRNG_OK;
}

int cckprng_addentropy(cckprng_ctx_t ctx, size_t nbytes, const void *seed) {
	prngInput(ctx->prng, (BYTE *)seed, (UINT)nbytes, 0, 0);
	ctx->bytes_since_entropy = 0;
	return CCKPRNG_OK;
}

int cckprng_generate(cckprng_ctx_t ctx, size_t nbytes, void *out) {
	BYTE *buffer = (BYTE *)out;
	while (nbytes > UINT32_MAX) {
		prngOutput(ctx->prng, buffer, UINT32_MAX);
		ctx->bytes_generated += UINT32_MAX;
		ctx->bytes_since_entropy += UINT32_MAX;

		buffer += UINT32_MAX;
		nbytes -= UINT32_MAX;
		nbytes = CC_MAX(nbytes, 0);
	}

	prngOutput(ctx->prng, buffer, (UINT)nbytes);
	ctx->bytes_generated += nbytes;
	ctx->bytes_since_entropy += nbytes;

	return CCKPRNG_OK;
}
