//
//  ccpad_pkcs7_ecb_decrypt.c
//  corecrypto
//
//  Created by Zormeister on 29/7/2025.
//

#include <corecrypto/ccmode.h>
#include <corecrypto/cc_priv.h>
#include <corecrypto/ccpad.h>

/* identical to ccpad_pkcs7_decrypt */
size_t ccpad_pkcs7_ecb_decrypt(const struct ccmode_ecb *ecb, ccecb_ctx *ecb_key, size_t nbytes, const void *in, void *out)
{
    /* hopefully nbytes is a multiple of the block size, otherwise that might be a problem ngl. */
    size_t block_size = ccecb_block_size(ecb);
    size_t blocks = nbytes / block_size;

    /* run decryption */
    ccecb_update(ecb, ecb_key, blocks, in, out);

    /* and return the size of the unpadded data. */
    return nbytes - ccpad_pkcs7_decode(block_size, out + (nbytes - block_size));
}
