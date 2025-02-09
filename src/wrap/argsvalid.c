//
//  argsvalid.c
//  corecrypto
//
//  Created by Zormeister on 8/2/2025.
//

#include <corecrypto/cc_priv.h>
#include <corecrypto/ccwrap_priv.h>

int ccwrap_argsvalid(void) {
    // Abort on call because I have no idea what gets passed in.
    cc_try_abort("i'm like, 99% sure this is an internal function - Zormeister");
    return CCERR_OK;
}
