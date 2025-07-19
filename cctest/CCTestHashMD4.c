//
//  CCTestHashMD4.c
//  cctest
//
//  Created by Zormeister on 26/1/2025.
//

#include "Test.h"
#include <corecrypto/ccmd4.h>
#include <stdbool.h>
#include <stdio.h>

/*
 * TODO: More comprehensive test cases.
 */

const uint8_t kCCHashTestMD4ExpectedResultNullString[] = { 0x31, 0xd6, 0xcf, 0xe0, 0xd1, 0x6a, 0xe9, 0x31, 0xb7, 0x3c, 0x59, 0xd7, 0xe0, 0xc0, 0x89, 0xc0 };
const uint8_t kCCHashTestMD4ExpectedResult2[]          = { 0x1b, 0xee, 0x69, 0xa4, 0x6b, 0xa8, 0x11, 0x18, 0x5c, 0x19, 0x47, 0x62, 0xab, 0xae, 0xae, 0x90 };
const uint8_t kCCHashTestMD4ExpectedResult3[]          = { 0x65, 0x78, 0xf2, 0x66, 0x4b, 0xc5, 0x6e, 0x0b, 0x5b, 0x3f, 0x85, 0xed, 0x26, 0xec, 0xc6, 0x7b };

CCTestHashCase kCCHashTestsMD4[] = {
    {
        NULL,
        0,
        16,
        kCCHashTestMD4ExpectedResultNullString,
    },
    {
        "",
        0,
        16,
        kCCHashTestMD4ExpectedResultNullString,
    },
    {
        "The quick brown fox jumps over the lazy dog",
        43,
        16,
        kCCHashTestMD4ExpectedResult2,
    },
    {
        "Test vector from febooti.com",
        28,
        16,
        kCCHashTestMD4ExpectedResult3,
    },
};

int TestMD4(void)
{
    const struct ccdigest_info *info = &ccmd4_di;
    for (int i = 0; i < sizeof(kCCHashTestsMD4) / sizeof(CCTestHashCase); i++) {
        ccdigest_di_decl(info, ctx);
        ccdigest_init(info, ctx);
        ccdigest_update(info, ctx, kCCHashTestsMD4[i].in_len, kCCHashTestsMD4[i].in);
        uint8_t hash_out[16];
        ccdigest_final(info, ctx, hash_out);
        if (memcmp(kCCHashTestsMD4[i].expected_out, hash_out, kCCHashTestsMD4[i].expected_out_len)) {
            printf("MD4 MISMATCH!!! (%d)\n", i);
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
            printf("MD4 MATCH! (%d)\n", i);
        }
        ccdigest_di_clear(info, ctx);
    }
    return 0;
}
