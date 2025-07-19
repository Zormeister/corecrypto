//
//  ccrc2_modes.c
//  corecrypto
//
//  Created by Zormeister on 2/6/2025.
//

#include <corecrypto/ccmode_factory.h>
#include <corecrypto/ccrc2.h>

CCMODE_CBC_FACTORY(rc2, encrypt)
CCMODE_CBC_FACTORY(rc2, decrypt)

CCMODE_OFB_FACTORY(rc2)

const struct ccmode_ecb *ccrc2_ecb_encrypt_mode(void)
{
    return &ccrc2_ltc_ecb_encrypt_mode;
}

const struct ccmode_ecb *ccrc2_ecb_decrypt_mode(void)
{
    return &ccrc2_ltc_ecb_decrypt_mode;
}
