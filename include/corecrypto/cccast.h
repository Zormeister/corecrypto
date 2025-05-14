//
//  cccast.h
//  corecrypto
//
//  Created by Zormeister on 12/5/25.
//

#ifndef _CORECRYPTO_CCCAST_H_
#define _CORECRYPTO_CCCAST_H_

#include <corecrypto/ccmode_impl.h>

#define CCCAST_BLOCK_SIZE 8
#define CCCAST_MIN_KEY_SIZE 5
#define CCCAST_MAX_KEY_SIZE 16

const struct ccmode_ecb *cccast_ecb_encrypt_mode(void);
const struct ccmode_ecb *cccast_ecb_decrypt_mode(void);

const struct ccmode_cbc *cccast_cbc_encrypt_mode(void);
const struct ccmode_cbc *cccast_cbc_decrypt_mode(void);

const struct ccmode_cfb *cccast_cfb_encrypt_mode(void);
const struct ccmode_cfb *cccast_cfb_decrypt_mode(void);

const struct ccmode_cfb8 *cccast_cfb8_encrypt_mode(void);
const struct ccmode_cfb8 *cccast_cfb8_decrypt_mode(void);

const struct ccmode_ctr *cccast_ctr_crypt_mode(void);

const struct ccmode_ofb *cccast_ofb_encrypt_mode(void);
const struct ccmode_ofb *cccast_ofb_decrypt_mode(void);

#endif /* _CORECRYPTO_CCCAST_H_ */
