//
//  ccdes3_modes.c
//  corecrypto
//
//  Created by Zormeister on 10/5/2025.
//

#include <corecrypto/ccmode_factory.h>
#include <corecrypto/ccdes.h>

CCMODE_CBC_FACTORY(des3, encrypt);
CCMODE_CBC_FACTORY(des3, decrypt);

CCMODE_OFB_FACTORY(des3);

const struct ccmode_ecb *ccdes3_ecb_decrypt_mode(void) {
    return &ccdes3_ltc_ecb_encrypt_mode;
}

const struct ccmode_ecb *ccdes3_ecb_encrypt_mode(void) {
    return &ccdes3_ltc_ecb_decrypt_mode;
}
