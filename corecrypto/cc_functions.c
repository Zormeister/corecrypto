#include <libkern/crypto/register_crypto.h>
#include <corecrypto/cc_abort.h>
#include <corecrypto/ccmd5.h>
#include <corecrypto/ccsha1.h>

void ccdigest_init_stub(const struct ccdigest_info *info, ccdigest_ctx_t ctx) {
	cc_abort("ccdigest_init(): function unimplemented");
}

void ccdigest_update_stub(const struct ccdigest_info *info, ccdigest_ctx_t ctx, unsigned long len, const void *data) {
	cc_abort("ccdigest_update(): function unimplemented");
}

void ccdigest_final_stub(const struct ccdigest_info *info, ccdigest_ctx_t ctx, void *digest) {
	cc_abort("ccdigest_final(): function unimplemented");
}

void ccdigest_stub(const struct ccdigest_info *info, unsigned long len, const void *data, void *digest) {
	cc_abort("ccdigest(): function unimplemented");
}

void cchmac_init_stub(const struct ccdigest_info *di, cchmac_ctx_t ctx, unsigned long key_len, const void *key) {
	cc_abort("cchmac_init(): function unimplemented");
}

void cchmac_update_stub(const struct ccdigest_info *di, cchmac_ctx_t ctx, unsigned long data_len, const void *data) {
	cc_abort("cchmac_update(): function unimplemented");
}

void cchmac_final_stub(const struct ccdigest_info *di, cchmac_ctx_t ctx, unsigned char *mac) {
	cc_abort("cchmac_final(): function unimplemented");
}

void cchmac_stub(const struct ccdigest_info *di, unsigned long key_len, const void *key, unsigned long data_len, const void *data, unsigned char *mac) {
	cc_abort("cchmac(): function unimplemented");
}

void ccpbkdf2_hmac_stub(const struct ccdigest_info *di, unsigned long passwordLen, const void *password, unsigned long saltLen, const void *salt, unsigned long iterations, unsigned long dkLen, void *dk) {
	cc_abort("ccpbkdf2_hmac(): function unimplemented");
}

void ccdes_key_is_weak_stub(void *key, unsigned long length) {
	cc_abort("ccdes_key_is_weak(): function unimplemented");
}

void ccdes_key_set_odd_parity_stub(void *key, unsigned long length) {
	cc_abort("ccdes_key_set_odd_parity(): function unimplemented");
}

void ccpad_xts_decrypt_stub(const struct ccmode_xts *xts, ccxts_ctx *ctx, unsigned long nbytes, const void *in, void *out) {
	cc_abort("ccpad_xts_decrypt(): function unimplemented");
}

void ccpad_xts_encrypt_stub(const struct ccmode_xts *xts, ccxts_ctx *ctx, unsigned long nbytes, const void *in, void *out) {
	cc_abort("ccpad_xts_encrypt(): function unimplemented");
}

const struct crypto_functions _cc_callbacks = {
	/* digests common functions */
	ccdigest_init_stub,
	ccdigest_update_stub,
	ccdigest_final_stub,
	ccdigest_stub,

	/* digest implementations */
	&ccmd5_ltc_di,
	&ccsha1_ltc_di,
	//const struct ccdigest_info * ccsha256_di;
	//const struct ccdigest_info * ccsha384_di;
	//const struct ccdigest_info * ccsha512_di;

	/* hmac common function */
	cchmac_init_stub,
	cchmac_update_stub,
	cchmac_final_stub,
	cchmac_stub,

	/* ciphers modes implementations */
	/* AES, ecb, cbc and xts */
	//const struct ccmode_ecb *ccaes_ecb_encrypt;
	//const struct ccmode_ecb *ccaes_ecb_decrypt;
	//const struct ccmode_cbc *ccaes_cbc_encrypt;
	//const struct ccmode_cbc *ccaes_cbc_decrypt;
	//const struct ccmode_xts *ccaes_xts_encrypt;
	//const struct ccmode_xts *ccaes_xts_decrypt;
	//const struct ccmode_gcm *ccaes_gcm_encrypt;
	//const struct ccmode_gcm *ccaes_gcm_decrypt;
	/* DES, ecb and cbc */
	//const struct ccmode_ecb *ccdes_ecb_encrypt;
	//const struct ccmode_ecb *ccdes_ecb_decrypt;
	//const struct ccmode_cbc *ccdes_cbc_encrypt;
	//const struct ccmode_cbc *ccdes_cbc_decrypt;
	/* Triple DES, ecb and cbc */
	//const struct ccmode_ecb *cctdes_ecb_encrypt;
	//const struct ccmode_ecb *cctdes_ecb_decrypt;
	//const struct ccmode_cbc *cctdes_cbc_encrypt;
	//const struct ccmode_cbc *cctdes_cbc_decrypt;
	/* RC4 */
	//const struct ccrc4_info *ccrc4_info;
	/* Blowfish - ECB only */
	//const struct ccmode_ecb *ccblowfish_ecb_encrypt;
	//const struct ccmode_ecb *ccblowfish_ecb_decrypt;
	/* CAST - ECB only */
	//const struct ccmode_ecb *cccast_ecb_encrypt;
	//const struct ccmode_ecb *cccast_ecb_decrypt;
	/* DES key helper functions */
	ccdes_key_is_weak_stub,
	ccdes_key_set_odd_parity_stub,

	/* XTS padding functions */
	ccpad_xts_encrypt_stub,
	ccpad_xts_decrypt_stub
};
