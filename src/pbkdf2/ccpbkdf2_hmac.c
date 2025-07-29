//
//  ccpbkdf2_hmac.c
//  corecrypto
//
//  Created by Zormeister on 30/6/2025.
//

#include "corecrypto/cc.h"
#include "corecrypto/cc_priv.h"
#include "corecrypto/ccn.h"
#include <corecrypto/cc_memory.h>
#include <corecrypto/cchmac.h>
#include <corecrypto/ccpbkdf2.h>

/*
 * read this for more info:
 * https://www.rfc-editor.org/rfc/rfc2898
 */

void PRF(const struct ccdigest_info *di, size_t passwordLen, const void *password,
         size_t length, const void *data,
         void *output)
{
    cchmac(di, passwordLen, password, length, data, output);
}

/* the base size of a workspace, though i'll change it to be dynamic. */
#define CCPKDDF2_WORKSPACE_BUFFER_SIZE_N(hlen) ccn_nof_size(hlen) + ccn_nof_size(4)

/* i wonder if i should run this all in the stack as opposed to allocating small pockets of memory */
#define CCPBKDF2_WORKSPACE_SALT_SIZE_N(saltLen) ccn_nof_size(saltLen) + ccn_nof_size(sizeof(uint32_t) * 2)

int ccpbkdf2_hmac(const struct ccdigest_info *di,
                  size_t passwordLen, const void *password,
                  size_t saltLen, const void *salt,
                  size_t iterations,
                  size_t dkLen, void *dk)
{
    size_t hLen = di->output_size;
    CC_WS_ALLOC_N(counter, CCPBKDF2_WORKSPACE_SALT_SIZE_N(saltLen)); /* Salt/Counter buffer */
    CC_WS_ALLOC_N(buffer1, CCPKDDF2_WORKSPACE_BUFFER_SIZE_N(hLen));
    CC_WS_ALLOC_N(buffer2, CCPKDDF2_WORKSPACE_BUFFER_SIZE_N(hLen));
    CC_WS_ALLOC_N(blockbuf, CCPKDDF2_WORKSPACE_BUFFER_SIZE_N(hLen));
    uint8_t *salt_ptr = (uint8_t *)counter->start;
    size_t nblocks = (dkLen + hLen - 1) / hLen;
    size_t remainder = dkLen % hLen;
    remainder = remainder ? remainder : hLen;
    size_t counterlen = saltLen + 4;

    /* copy the salt into the counter */
    cc_memcpy(counter->start, salt, saltLen);

    for (int cnt = 0; cnt < nblocks; cnt++) {
        /* compute U_1 */
        int block = cnt + 1;
        size_t outLen = block != nblocks ? hLen : remainder;

        /* encode the counter */
        for (int i = 0; i < 4; i++) {
            salt_ptr[saltLen + i] = (block >> 8 * (3 - i)) & 0xff;
        }

        /* run the PRF for U_1 */
        PRF(di, passwordLen, password, counterlen, salt, buffer1->start);

        cc_memcpy(blockbuf->start, buffer1->start, counterlen);

        for (int iter = 1; iter < iterations; iter++) {
            PRF(di, passwordLen, password, hLen, buffer1->start, buffer2->start);
            cc_memcpy(buffer1->start, buffer2->start, hLen);
            cc_xor(hLen, blockbuf->start, blockbuf->start, buffer1->start);
        }

        cc_memcpy(dk + (block * hLen), blockbuf->start, outLen);
    }

    CC_WS_FREE_N(counter, CCPBKDF2_WORKSPACE_SALT_SIZE_N(saltLen));
    CC_WS_FREE_N(buffer1, CCPKDDF2_WORKSPACE_BUFFER_SIZE_N(hLen));
    CC_WS_FREE_N(buffer2, CCPKDDF2_WORKSPACE_BUFFER_SIZE_N(hLen));
    CC_WS_FREE_N(blockbuf, CCPKDDF2_WORKSPACE_BUFFER_SIZE_N(hLen));
    return CCERR_OK;
}
