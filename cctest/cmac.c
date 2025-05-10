//
//  cmac.c
//  cctest
//
//  Created by Zormeister on 13/4/25.
//  Copyright © 2025 William Kent. All rights reserved.
//

#include <corecrypto/ccaes.h>
#include <corecrypto/cccmac_priv.h>

static const uint8_t key[] = {0x2b,0x7e,0x15,0x16,0x28,0xae,0xd2,0xa6,0xab,0xf7,0x15,0x88,0x09,0xcf,0x4f,0x3c};

void TestCMAC() {
    //cccmac_mode_decl(ccaes_cbc_encrypt_mode(), cmac);

    //cccmac_init(ccaes_cbc_encrypt_mode(), cmac, CCAES_KEY_SIZE_128, key);
}
