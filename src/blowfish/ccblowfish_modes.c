//
//  ccblowfish_modes.c
//  corecrypto
//
//  Created by Zormeister on 12/5/2025.
//

#include "ccblowfish_ltc_internal.h"
#include <corecrypto/ccblowfish.h>
#include <corecrypto/ccmode_factory.h>

CCMODE_CBC_FACTORY(blowfish, encrypt);
CCMODE_CBC_FACTORY(blowfish, decrypt);

CCMODE_OFB_FACTORY(blowfish);

CCMODE_CFB_FACTORY(blowfish, cfb, encrypt);
CCMODE_CFB_FACTORY(blowfish, cfb, decrypt);
CCMODE_CFB_FACTORY(blowfish, cfb8, decrypt);
CCMODE_CFB_FACTORY(blowfish, cfb8, encrypt);

const struct ccmode_ecb *ccblowfish_ecb_encrypt_mode(void)
{
    return &ccblowfish_ltc_ecb_encrypt_mode;
}

const struct ccmode_ecb *ccblowfish_ecb_decrypt_mode(void)
{
    return &ccblowfish_ltc_ecb_decrypt_mode;
}
