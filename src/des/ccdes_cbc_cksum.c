//
//  ccdes_cbc_sksum.c
//  corecrypto
//
//  Created by Zormeister on 20/5/2025.
//

#include <corecrypto/cc_priv.h>
#include <corecrypto/ccdes.h>

uint32_t ccdes_cbc_cksum(const void *in, void *out, size_t length, const void *key, size_t key_nbytes, const void *ivec)
{
    uint32_t work[2];

    CC_LOAD32_BE(work[0], in);
    CC_LOAD32_BE(work[1], in + 4);

    return 0;
}
