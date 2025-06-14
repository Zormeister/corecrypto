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

CCMODE_CBC_FACTORY(cast, encrypt);
CCMODE_CBC_FACTORY(cast, decrypt);

CCMODE_OFB_FACTORY(cast);

CCMODE_CFB_FACTORY(cast, cfb, encrypt);
CCMODE_CFB_FACTORY(cast, cfb, decrypt);
CCMODE_CFB_FACTORY(cast, cfb8, decrypt);
CCMODE_CFB_FACTORY(cast, cfb8, encrypt);

const struct ccmode_ecb *cccast_ecb_encrypt_mode(void) {
    return &cccast_eay_ecb_encrypt_mode;
}

const struct ccmode_ecb *cccast_ecb_decrypt_mode(void) {
    return &cccast_eay_ecb_decrypt_mode;
}
