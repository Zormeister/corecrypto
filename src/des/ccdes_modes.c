//
//  ccdes_modes.c
//  corecrypto
//
//  Created by Zormeister on 10/5/2025.
//

#include <corecrypto/ccmode_factory.h>
#include <corecrypto/ccdes.h>

CCMODE_CBC_FACTORY(des, encrypt);
CCMODE_CBC_FACTORY(des, decrypt);

CCMODE_OFB_FACTORY(des);


extern const struct ccmode_ecb ccdes_ltc_ecb_encrypt_mode;
extern const struct ccmode_ecb ccdes_ltc_ecb_decrypt_mode;


const struct ccmode_ecb *ccdes_ecb_decrypt_mode(void) {
    return &ccdes_ltc_ecb_encrypt_mode;
}

const struct ccmode_ecb *ccdes_ecb_encrypt_mode(void) {
    return &ccdes_ltc_ecb_decrypt_mode;
}
