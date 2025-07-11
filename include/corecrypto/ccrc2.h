//
//  ccrC2.h
//  corecrypto
//
//  Created by Zormeister on 30/5/2025.
//

#ifndef _CORECRYPTO_CCRC2_H_
#define _CORECRYPTO_CCRC2_H_

#include <corecrypto/ccmode.h>
#include <corecrypto/ccmode_impl.h>

#define CCRC2_BLOCK_SIZE 8

extern const struct ccmode_ecb ccrc2_ltc_ecb_encrypt_mode;
extern const struct ccmode_ecb ccrc2_ltc_ecb_decrypt_mode;

const struct ccmode_ecb *ccrc2_ecb_decrypt_mode(void);
const struct ccmode_ecb *ccrc2_ecb_encrypt_mode(void);

const struct ccmode_cbc *ccrc2_cbc_decrypt_mode(void);
const struct ccmode_cbc *ccrc2_cbc_encrypt_mode(void);

const struct ccmode_cfb *ccrc2_cfb_decrypt_mode(void);
const struct ccmode_cfb *ccrc2_cfb_encrypt_mode(void);

const struct ccmode_cfb8 *ccrc2_cfb8_decrypt_mode(void);
const struct ccmode_cfb8 *ccrc2_cfb8_encrypt_mode(void);

const struct ccmode_ctr *ccrc2_ctr_crypt_mode(void);

const struct ccmode_ofb *ccrc2_ofb_crypt_mode(void);

#endif /* _CORECRYPTO_CCRC2_H_ */