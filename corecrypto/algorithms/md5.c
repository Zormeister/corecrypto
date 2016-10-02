#include <corecrypto/ccmd5.h>
#include <corecrypto/cc_abort.h>

static void ccmd5_ltc_compress(ccdigest_state_t state, unsigned long nblocks, const void *data) {
	cc_abort("ccmd5_ltc_di->compress(): function unimplemented");
}

static void ccmd5_ltc_final(const struct ccdigest_info *di, ccdigest_state_t state, unsigned char *digest) {
	cc_abort("ccmd5_ltc_di->final(): function unimplemented");
}

const struct ccdigest_info ccmd5_ltc_di = {
	CCMD5_OUTPUT_SIZE, CCMD5_STATE_SIZE, CCMD5_BLOCK_SIZE, 10,
	(unsigned char *) CC_DIGEST_OID_MD5,
	NULL,
	ccmd5_ltc_compress,
	ccmd5_ltc_final
};

const uint32_t ccmd5_initial_state[4] = {
	0, 0, 0, 0
};

const struct ccdigest_info *ccmd5_di(void) {
	return &ccmd5_ltc_di;
}
