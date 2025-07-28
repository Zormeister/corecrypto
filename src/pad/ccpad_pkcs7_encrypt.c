//
//  ccpad_pkcs7_encrypt.c
//  corecrypto
//
//  Created by Zormeister on 29/7/2025.
//

#include <corecrypto/ccmode.h>
#include <corecrypto/cc_priv.h>
#include <corecrypto/ccpad.h>

/* random but can't this hypothetically be abused, the out pointer doesn't have a length on the contents. */
size_t ccpad_pkcs7_encrypt(const struct ccmode_cbc *cbc, cccbc_ctx *ctx, cccbc_iv *iv, size_t nbytes, const void *in, void *out)
{
    /* first, calculate how many blocks we have (regardless of the number of bytes) */
    size_t block_size = cccbc_block_size(cbc);
    size_t blocks_bytes = (nbytes / block_size) * cccbc_block_size(cbc);
    size_t remaining_size = nbytes - blocks_bytes;
    size_t padding = block_size - remaining_size;

    /* now that we've ran that math, run encryption for the blocks that we do have. */
    cccbc_update(cbc, ctx, iv, (nbytes / block_size), in, out);

    /* progress the pointers forward because we need to be at the last snippet of data */
    in += blocks_bytes;
    out += blocks_bytes;

    /* using a neat trick that uses the out buffer as a scratch space until the cbc encryption */
    cc_memcpy(out, in, remaining_size);

    /* set the padding in the scratch space (which is block size - remaining size, i believe) */
    cc_memset(out + remaining_size, padding, padding);

    /* now that we've constructed the last block, encrypt it */
    cccbc_update(cbc, ctx, iv, 1, out, out);

    /* and return the full size of the freshly rencrypted data. */
    return (blocks_bytes + remaining_size + padding);
}
