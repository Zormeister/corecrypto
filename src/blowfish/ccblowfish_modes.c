//
//  ccblowfish_modes.c
//  corecrypto
//
//  Created by Zormeister on 12/5/2025.
//

#include <corecrypto/ccmode_factory.h>
#include <corecrypto/ccblowfish.h>
#include "ccblowfish_ltc_internal.h"

CCMODE_CBC_FACTORY(blowfish, encrypt)
CCMODE_CBC_FACTORY(blowfish, decrypt)

const struct ccmode_ecb *ccblowfish_ecb_encrypt_mode() {
    return &ccblowfish_ltc_ecb_encrypt_mode;
}

const struct ccmode_ecb *ccblowfish_ecb_decrypt_mode() {
    return &ccblowfish_ltc_ecb_decrypt_mode;
}
