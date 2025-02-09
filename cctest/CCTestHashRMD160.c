//
//  CCTestHashRMD160.c
//  cctest
//
//  Created by Zormeister on 9/2/2025.
//

#include "Test.h"
#include <corecrypto/ccripemd.h>
#include <stdbool.h>
#include <stdio.h>

/*
 * TODO: More comprehensive test cases.
 */

const uint8_t kCCHashTestRMD160ExpectedResultNullString[] = {0x9c,0x11,0x85,0xa5,0xc5,0xe9,0xfc,0x54,0x61,0x28,0x08,0x97,0x7e,0xe8,0xf5,0x48,0xb2,0x25,0x8d,0x31};
const uint8_t kCCHashTestRMD160ExpectedResult2[] = {0x37,0xf3,0x32,0xf6,0x8d,0xb7,0x7b,0xd9,0xd7,0xed,0xd4,0x96,0x95,0x71,0xad,0x67,0x1c,0xf9,0xdd,0x3b};
const uint8_t kCCHashTestRMD160ExpectedResult3[] = {0x4e,0x1f,0xf6,0x44,0xca,0x9f,0x6e,0x86,0x16,0x7c,0xcb,0x30,0xff,0x27,0xe0,0xd8,0x4c,0xeb,0x2a,0x61};

CCTestHashCase kCCHashTestsRMD160[] = {
    {
        NULL,
        0,
        sizeof(kCCHashTestRMD160ExpectedResultNullString),
        kCCHashTestRMD160ExpectedResultNullString,
    },
    {
        "",
        0,
        sizeof(kCCHashTestRMD160ExpectedResultNullString),
        kCCHashTestRMD160ExpectedResultNullString,
    },
    {
        "The quick brown fox jumps over the lazy dog",
        43,
        sizeof(kCCHashTestRMD160ExpectedResult2),
        kCCHashTestRMD160ExpectedResult2,
    },
    {
        "Test vector from febooti.com",
        28,
        sizeof(kCCHashTestRMD160ExpectedResult3),
        kCCHashTestRMD160ExpectedResult3,
    },
};

// errrm so we stack buffer overflow after these tests are done. how do i fix that.
int TestRMD160(void) {
    const struct ccdigest_info *info = &ccrmd160_di;
    for (int i = 0; i < sizeof(kCCHashTestsRMD160) / sizeof(CCTestHashCase); i++) {
        ccdigest_di_decl(info, ctx);
        ccdigest_init(info, ctx);
        ccdigest_update(info, ctx, kCCHashTestsRMD160[i].in_len, kCCHashTestsRMD160[i].in);
        uint8_t hash_out[16];
        ccdigest_final(info, ctx, hash_out);
        if (memcmp(kCCHashTestsRMD160[i].expected_out, hash_out, kCCHashTestsRMD160[i].expected_out_len)) {
            printf("RMD160 MISMATCH!!! (%d)\n", i);
            printf("recieved:\n");
            printf("\t %x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x\n", hash_out[0], hash_out[1],
                   hash_out[2], hash_out[3],
                   hash_out[4], hash_out[5],
                   hash_out[6], hash_out[7],
                   hash_out[8], hash_out[9],
                   hash_out[10], hash_out[11],
                   hash_out[12], hash_out[13],
                   hash_out[14], hash_out[15]);
            ccdigest_di_clear(info, ctx);
            return -1;
        } else {
            printf("RMD160 MATCH! (%d)\n", i);
        }
        ccdigest_di_clear(info, ctx);
    }
    return 0;
}
