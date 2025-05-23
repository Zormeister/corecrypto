//
//  ccrc4_eay.c
//  corecrypto
//
//  Created by Zormeister on 23/5/2025.
//

#include "ccrc4_eay_internal.h"
#include <corecrypto/cc_error.h>
#include <corecrypto/ccrc4.h>

static void ccrc4_eay_init(ccrc4_ctx *ctx, size_t key_len, const void *key) {
    eay_RC4_set_key((RC4_KEY *)ctx, key_len, key);
}

static void ccrc4_eay_crypt(ccrc4_ctx *ctx, size_t nbytes, const void *in, void *out) {
    eay_RC4((RC4_KEY *)ctx, nbytes, in, out);
}

const struct ccrc4_info ccrc4_eay = {
    .size = ccn_sizeof_size(sizeof(RC4_KEY)),
    .init = ccrc4_eay_init,
    .crypt = ccrc4_eay_crypt,
};
