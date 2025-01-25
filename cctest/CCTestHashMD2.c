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

const uint8_t kCCHashTestExpectedResultNullString[] = {0x83,0x50,0xe5,0xa3,0xe2,0x4c,0x15,0x3d,0xf2,0x27,0x5c,0x9f,0x80,0x69,0x27,0x73};

CCTestHashCase kCCHashTestsMD2[] = {
    {
        "",
        0,
        16,
        kCCHashTestExpectedResultNullString,
    }
};

int TestMD2(void) {
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
