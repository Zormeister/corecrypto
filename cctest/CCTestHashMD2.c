//
//  CCTestHashMD2.c
//  cctest
//
//  Created by Zormeister on 25/1/2025.
//

#include "Test.h"
#include <corecrypto/ccmd2.h>
#include <stdbool.h>
#include <stdio.h>

/*
 * TODO: More comprehensive test cases.
 */

const uint8_t kCCHashTestMD2ExpectedResultNullString[] = { 0x83, 0x50, 0xe5, 0xa3, 0xe2, 0x4c, 0x15, 0x3d, 0xf2, 0x27, 0x5c, 0x9f, 0x80, 0x69, 0x27, 0x73 };
const uint8_t kCCHashTestMD2ExpectedResult2[]          = { 0x03, 0xd8, 0x5a, 0x0d, 0x62, 0x9d, 0x2c, 0x44, 0x2e, 0x98, 0x75, 0x25, 0x31, 0x9f, 0xc4, 0x71 };
const uint8_t kCCHashTestMD2ExpectedResult3[]          = { 0xdb, 0x12, 0x8d, 0x6e, 0x0d, 0x20, 0xa1, 0x19, 0x2a, 0x6b, 0xd1, 0xfa, 0xde, 0x40, 0x11, 0x50 };

CCTestHashCase kCCHashTestsMD2[] = {
    {
        NULL,
        0,
        16,
        kCCHashTestMD2ExpectedResultNullString,
    },
    {
        "",
        0,
        16,
        kCCHashTestMD2ExpectedResultNullString,
    },
    {
        "The quick brown fox jumps over the lazy dog",
        43,
        16,
        kCCHashTestMD2ExpectedResult2,
    },
    {
        "Test vector from febooti.com",
        28,
        16,
        kCCHashTestMD2ExpectedResult3,
    },
};

int TestMD2(void)
{
    const struct ccdigest_info *info = &ccmd2_di;
    for (int i = 0; i < sizeof(kCCHashTestsMD2) / sizeof(CCTestHashCase); i++) {
        ccdigest_di_decl(info, ctx);
        ccdigest_init(info, ctx);
        ccdigest_update(info, ctx, kCCHashTestsMD2[i].in_len, kCCHashTestsMD2[i].in);
        uint8_t hash_out[16];
        ccdigest_final(info, ctx, hash_out);
        if (memcmp(kCCHashTestsMD2[i].expected_out, hash_out, kCCHashTestsMD2[i].expected_out_len)) {
            printf("MD2 MISMATCH!!! (%d)\n", i);
            printf("recieved:\n");
            printf("\t %x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x\n", hash_out[0], hash_out[1],
                   hash_out[2], hash_out[3],
                   hash_out[4], hash_out[5],
                   hash_out[6], hash_out[7],
                   hash_out[8], hash_out[9],
                   hash_out[10], hash_out[11],
                   hash_out[12], hash_out[13],
                   hash_out[14], hash_out[15]);
            return -1;
        } else {
            printf("MD2 MATCH! (%d)\n", i);
        }
        ccdigest_di_clear(info, ctx);
    }
    return 0;
}
