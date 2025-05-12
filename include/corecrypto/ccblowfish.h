//
//  ccblowfish.h
//  corecrypto
//
//  Created by Zormeister on 14/4/25.
//

#ifndef _CORECRYPTO_CCBLOWFISH_H_
#define _CORECRYPTO_CCBLOWFISH_H_

#include <corecrypto/cc_config.h>
#include <corecrypto/ccmode.h>

#define CCBLOWFISH_BLOCK_SIZE 8
#define CCBLOWFISH_MIN_KEY_SIZE 8
#define CCBLOWFISH_MAX_KEY_SIZE 72

const struct ccmode_ecb *ccblowfish_ecb_encrypt_mode();
const struct ccmode_ecb *ccblowfish_ecb_decrypt_mode();

const struct ccmode_cbc *ccblowfish_cbc_encrypt_mode();
const struct ccmode_cbc *ccblowfish_cbc_decrypt_mode();

const struct ccmode_cfb *ccblowfish_cfb_encrypt_mode();
const struct ccmode_cfb *ccblowfish_cfb_decrypt_mode();

const struct ccmode_cfb8 *ccblowfish_cfb8_encrypt_mode();
const struct ccmode_cfb8 *ccblowfish_cfb8_decrypt_mode();

const struct ccmode_ctr *ccblowfish_ctr_crypt_mode();

const struct ccmode_ofb *ccblowfish_ofb_encrypt_mode();
const struct ccmode_ofb *ccblowfish_ofb_decrypt_mode();

#endif /* _CORECRYPTO_CCBLOWFISH_H_ */
