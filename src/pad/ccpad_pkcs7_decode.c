//
//  ccpad_pkcs7_decode.c
//  corecrypto
//
//  Created by Zormeister on 28/7/2025.
//

#include <corecrypto/cc_priv.h>
#include <corecrypto/ccpad.h>

size_t ccpad_pkcs7_decode(const size_t block_size, const uint8_t *last_block)
{
    /* read the last byte of the block, PKCS#7 specifies that the padding is the hexadecimal value of the padding size. */
    return last_block[block_size - 1];
}
