//
//  cccast_modes.c
//  corecrypto
//
//  Created by Zormeister on 13/5/2025.
//

/* EAY modes */

#include <corecrypto/ccmode_factory.h>
#include <corecrypto/cccast.h>
#include "cccast_eay_internal.h"

CCMODE_CBC_FACTORY(cast, encrypt)
CCMODE_CBC_FACTORY(cast, decrypt)

const struct ccmode_ecb *cccast_ecb_encrypt_mode() {
    return &cccast_eay_ecb_encrypt_mode;
}

const struct ccmode_ecb *cccast_ecb_decrypt_mode() {
    return &cccast_eay_ecb_decrypt_mode;
}
