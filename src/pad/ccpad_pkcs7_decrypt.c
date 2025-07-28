//
//  ccpad_pkcs7_decrypt.c
//  corecrypto
//
//  Created by Zormeister on 29/7/2025.
//

#include <corecrypto/ccmode.h>
#include <corecrypto/cc_priv.h>
#include <corecrypto/ccpad.h>

size_t ccpad_pkcs7_decrypt(const struct ccmode_cbc *cbc, cccbc_ctx *ctx, cccbc_iv *iv, size_t nbytes, const void *in, void *out)
{
    /* hopefully nbytes is a multiple of the block size, otherwise that might be a problem ngl. */
    size_t block_size = cccbc_block_size(cbc);
    size_t blocks = nbytes / block_size;

    /* run decryption */
    cccbc_update(cbc, ctx, iv, blocks, in, out);

    /* and return the size of the unpadded data. */
    return nbytes - ccpad_pkcs7_decode(block_size, out + (nbytes - block_size));
}
