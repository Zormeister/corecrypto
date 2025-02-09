#include "register_crypto.h"
#include <corecrypto/cc_abort.h>
#include <corecrypto/ccmd5.h>
#include <corecrypto/ccsha1.h>
#include <corecrypto/ccdigest_priv.h>
#include <corecrypto/cchmac.h>
#include "../dummy/pdcrypto_dummy.h"

extern const struct ccdigest_info pdcmd5_di;
extern const struct ccmode_ecb pdcaes_ecb_encrypt;
extern const struct ccmode_ecb pdcaes_ecb_decrypt;
extern const struct ccmode_cbc pdcaes_cbc_encrypt;
extern const struct ccmode_cbc pdcaes_cbc_decrypt;
extern const struct ccdigest_info ccsha256_ltc_di;

const struct crypto_functions pdcrypto_internal_functions = {
	.ccdigest_init_fn = ccdigest_init,
	.ccdigest_update_fn = ccdigest_update,
	.ccmd5_di = &pdcmd5_di,
	.ccsha1_di = &ccsha1_ltc_di,

	.ccdigest_final_fn = ccdigest_final,
	.ccdigest_fn = ccdigest,
	.ccsha256_di = &ccsha256_ltc_di,
	.ccsha384_di = &ccsha384_ltc_di,
	.ccsha512_di = &ccsha512_ltc_di,
	.cchmac_init_fn = cchmac_init,
	.cchmac_update_fn = cchmac_update,
	.cchmac_final_fn = cchmac_final,
	.cchmac_fn = cchmac,
	.ccaes_ecb_encrypt = &pdcaes_ecb_encrypt,
	.ccaes_ecb_decrypt = &pdcaes_ecb_decrypt,
	.ccaes_cbc_encrypt = &pdcaes_cbc_encrypt,
	.ccaes_cbc_decrypt = &pdcaes_cbc_decrypt,
	.ccaes_xts_encrypt = &pdcaes_xts_encrypt_dummy,
	.ccaes_xts_decrypt = &pdcaes_xts_decrypt_dummy,
	.ccaes_gcm_encrypt = &pdcaes_gcm_encrypt_dummy,
	.ccaes_gcm_decrypt = &pdcaes_gcm_decrypt_dummy,
	.ccdes_ecb_encrypt = &pdcdes_ecb_encrypt_dummy,
	.ccdes_ecb_decrypt = &pdcdes_ecb_decrypt_dummy,
	.ccdes_cbc_encrypt = &pdcdes_cbc_encrypt_dummy,
	.ccdes_cbc_decrypt = &pdcdes_cbc_decrypt_dummy,
	.cctdes_ecb_encrypt = &pdctdes_ecb_encrypt_dummy,
	.cctdes_ecb_decrypt = &pdctdes_ecb_decrypt_dummy,
	.cctdes_cbc_encrypt = &pdctdes_cbc_encrypt_dummy,
	.cctdes_cbc_decrypt = &pdctdes_cbc_decrypt_dummy,
	.ccrc4_info = &pdcrc4_info_dummy,
	.ccblowfish_ecb_encrypt = &pdcblowfish_ecb_encrypt_dummy,
	.ccblowfish_ecb_decrypt = &pdcblowfish_ecb_decrypt_dummy,
	.cccast_ecb_encrypt = &pdccast_ecb_encrypt_dummy,
	.cccast_ecb_decrypt = &pdccast_ecb_decrypt_dummy,
	.ccdes_key_is_weak_fn = pdcdes_key_is_weak_fn_dummy,
	.ccdes_key_set_odd_parity_fn = pdcdes_key_set_odd_parity_fn_dummy,
	.ccpad_xts_encrypt_fn = pdcpad_xts_encrypt_fn_dummy,
	.ccpad_xts_decrypt_fn = pdcpad_xts_decrypt_fn_dummy,

	.ccrng_fn = ccrng
};

