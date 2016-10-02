#include <corecrypto/ccsha1.h>
#include <corecrypto/cc_abort.h>

static void ccsha1_ltc_compress(ccdigest_state_t state, unsigned long nblocks, const void *data) {
	cc_abort("ccsha1_ltc_di->compress(): function unimplemented");
}

static void ccsha1_ltc_final(const struct ccdigest_info *di, ccdigest_state_t state, unsigned char *digest) {
	cc_abort("ccsha1_ltc_di->final(): function unimplemented");
}

const struct ccdigest_info ccsha1_ltc_di = {
	CCSHA1_OUTPUT_SIZE, CCSHA1_STATE_SIZE, CCSHA1_BLOCK_SIZE,
	ccoid_sha1_len, ccoid_sha1,
	NULL,
	ccsha1_ltc_compress,
	ccsha1_ltc_final
};

const struct ccdigest_info ccsha1_eay_di = {
	CCSHA1_OUTPUT_SIZE, CCSHA1_STATE_SIZE, CCSHA1_BLOCK_SIZE,
	ccoid_sha1_len, ccoid_sha1,
	NULL,
	ccsha1_ltc_compress,
	ccsha1_ltc_final
};

const uint32_t ccsha1_initial_state[5] = {
	0, 0, 0, 0, 0
};

const struct ccdigest_info *ccsha1_di(void) {
	return &ccsha1_ltc_di;
}

void ccsha1_final(const struct ccdigest_info *di, ccdigest_ctx_t ctx, unsigned char *digest) {
	cc_abort("ccsha1_final(): function unimplemented");
}
