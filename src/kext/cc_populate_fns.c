//
//  cc_populate_fns.c
//  corecrypto
//
//  Created by Zormeister on 10/5/2025.
//

#if __has_include(<libkern/crypto/register_crypto.h>)
#include <libkern/crypto/register_crypto.h>
#else
#include "register_crypto.h"
#endif

#include <corecrypto/ccaes.h>
#include <corecrypto/ccblowfish.h>
#include <corecrypto/cccast.h>
#include <corecrypto/ccdes.h>
#include <corecrypto/ccdigest_priv.h>
#include <corecrypto/cchmac.h>
#include <corecrypto/ccmd5.h>
#include <corecrypto/ccrc4.h>
#include <corecrypto/ccsha1.h>
#include <corecrypto/ccsha2.h>

/*
 * Darwin has a tendency to change how the crypto API implements functions
 * For example, Darwin 20 removed the need for:
 * - CAST
 * - Blowfish
 * - XTS enc/dec padding
 * - RC4
 * In the kernel space, which means I'll either have to:
 * - Have a user-defined Darwin target and modify the local register_crypto.h header / disable functionality in cc_populate_fns
 * - Have a branch for each Darwin version needing an update
 *
 * Both of these sound like a PITA but I've gotta do what I've gotta do.
 *
 * XNU versions worthy of note:
 * - 7195.50.7.100.1
 * - 8792.41.9
 * - 8792.61.2
 * - 8796.101.5
 */

void cc_populate_fns(crypto_functions_t fns)
{
#if CCKEXT_TRACE
    printf("corecrypto: populating functions for XNU\n");
#endif

    /* AES modes */
    fns->ccaes_cbc_encrypt = ccaes_cbc_encrypt_mode();
    fns->ccaes_cbc_decrypt = ccaes_cbc_decrypt_mode();
    fns->ccaes_ecb_encrypt = ccaes_ecb_encrypt_mode();
    fns->ccaes_ecb_decrypt = ccaes_ecb_decrypt_mode();

    /* Blowfish functions */
    fns->ccblowfish_ecb_encrypt = ccblowfish_ecb_encrypt_mode();
    fns->ccblowfish_ecb_decrypt = ccblowfish_ecb_decrypt_mode();

    /* CAST functions */
    fns->cccast_ecb_encrypt = cccast_ecb_encrypt_mode();
    fns->cccast_ecb_decrypt = cccast_ecb_decrypt_mode();

    /* DES functions */
    fns->ccdes_key_is_weak_fn = &ccdes_key_is_weak;
    fns->ccdes_key_set_odd_parity_fn = &ccdes_key_set_odd_parity;
    fns->ccdes_cbc_encrypt = ccdes_cbc_encrypt_mode();
    fns->ccdes_cbc_decrypt = ccdes_cbc_decrypt_mode();
    fns->ccdes_ecb_encrypt = ccdes_ecb_encrypt_mode();
    fns->ccdes_ecb_decrypt = ccdes_ecb_decrypt_mode();

    /* Triple DES functions */
    fns->cctdes_cbc_encrypt = ccdes3_cbc_encrypt_mode();
    fns->cctdes_cbc_decrypt = ccdes3_cbc_decrypt_mode();
    fns->cctdes_ecb_encrypt = ccdes3_ecb_encrypt_mode();
    fns->cctdes_ecb_decrypt = ccdes3_ecb_decrypt_mode();

    /* HMAC functions */
    fns->cchmac_fn = &cchmac;
    fns->cchmac_init_fn = &cchmac_init;
    fns->cchmac_update_fn = &cchmac_update;
    fns->cchmac_final_fn = &cchmac_final;

    /* digest functions */
    fns->ccdigest_fn = &ccdigest;
    fns->ccdigest_init_fn = &ccdigest_init;
    fns->ccdigest_update_fn = &ccdigest_update;
    fns->ccdigest_final_fn = &ccdigest_final;

    /* Hashing digest info pointers */
    fns->ccsha1_di = ccsha1_di();
    fns->ccsha256_di = ccsha256_di();
    fns->ccsha384_di = ccsha384_di();
    fns->ccsha512_di = ccsha512_di();
    fns->ccmd5_di = ccmd5_di();

    /* RC4 */
    fns->ccrc4_info = ccrc4();

#if CCKEXT_TRACE
    printf("corecrypto: finished populating implemented functions.\n");
#endif
}
