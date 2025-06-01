//
//  cctest.c
//  corecrypto
//
//  Created by Zormeister on 30/5/2025.
//

#include <corecrypto/cc_priv.h>
#include <corecrypto/cc_debug.h>
#include "cctest_internal.h"

cctest_digest_callback digests[crypto_digest_max];
cctest_cipher_callback ciphers[crypto_cipher_max][crypto_cipher_mode_max];

void cctest_init(void) {
    cc_printf("cctest: initializing.\n");
}
