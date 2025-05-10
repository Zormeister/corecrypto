//
//  cc_populate_fns_dummy.c
//  corecrypto
//
//  Created by Zormeister on 10/5/2025.
//

#if __has_include(<libkern/crypto/register_crypto.h>)
#include <libkern/crypto/register_crypto.h>
#else
#include "register_crypto.h"
#endif

#include "../dummy/pdcrypto_dummy.h"

void cc_populate_fns_dummy(crypto_functions_t fns) {
#if CCKEXT_TRACE
    printf("corecrypto: populating dummies for XNU\n");
#endif

    /* AES dummies */
    fns->ccaes_gcm_decrypt = &pdcaes_gcm_decrypt_dummy;
    fns->ccaes_gcm_encrypt = &pdcaes_gcm_encrypt_dummy;
    fns->ccaes_xts_decrypt = &pdcaes_xts_decrypt_dummy;
    fns->ccaes_xts_encrypt = &pdcaes_xts_encrypt_dummy;

    /* Blowfish dummies */
    fns->ccblowfish_ecb_decrypt = &pdcblowfish_ecb_encrypt_dummy;
    fns->ccblowfish_ecb_encrypt = &pdcblowfish_ecb_encrypt_dummy;

    /* CAST dummies */
    fns->cccast_ecb_encrypt = &pdccast_ecb_encrypt_dummy;
    fns->cccast_ecb_decrypt = &pdccast_ecb_decrypt_dummy;

    /* DES dummies */
    fns->ccdes_key_set_odd_parity_fn = pdcdes_key_set_odd_parity_fn_dummy;

    /* Padding dummies */
    fns->ccpad_xts_decrypt_fn = pdcpad_xts_encrypt_fn_dummy;
    fns->ccpad_xts_encrypt_fn = pdcpad_xts_decrypt_fn_dummy;

    /* RC4 dummy */
    fns->ccrc4_info = &pdcrc4_info_dummy;

    /* RNG dummy */
    fns->ccrng_fn = ccrng; /* I consider this a dummy because it returns the KPRNG. The **real** CCRNG is an NIST CTR DRBG using AES */

#if CCKEXT_TRACE
    printf("corecrypto: finished populating dummies.\n");
#endif
}
