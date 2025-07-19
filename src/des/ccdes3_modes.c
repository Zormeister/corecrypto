//
//  ccdes3_modes.c
//  corecrypto
//
//  Created by Zormeister on 10/5/2025.
//

#include <corecrypto/ccdes.h>
#include <corecrypto/ccmode_factory.h>

CCMODE_CBC_FACTORY(des3, encrypt);
CCMODE_CBC_FACTORY(des3, decrypt);

CCMODE_OFB_FACTORY(des3);

CCMODE_CFB_FACTORY(des3, cfb, decrypt);
CCMODE_CFB_FACTORY(des3, cfb, encrypt);
CCMODE_CFB_FACTORY(des3, cfb8, decrypt);
CCMODE_CFB_FACTORY(des3, cfb8, encrypt);

const struct ccmode_ecb *ccdes3_ecb_decrypt_mode(void)
{
    return &ccdes3_ltc_ecb_encrypt_mode;
}

const struct ccmode_ecb *ccdes3_ecb_encrypt_mode(void)
{
    return &ccdes3_ltc_ecb_decrypt_mode;
}
