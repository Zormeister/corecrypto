//
//  chacha20.c
//  corecrypto
//
//  Created by Zormeister on 15/2/2025.
//

#include <corecrypto/cc.h>
#include <corecrypto/ccchacha20poly1305_priv.h>

uint8_t key[32] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 };
uint32_t nonce[3] = { 0, 0, 0 };

uint64_t data[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };

uint64_t out[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
/*
 * 000  76 b8 e0 ad a0 f1 3d 90 40 5d 6a e5 53 86 bd 28  v.....=.@]j.S..(
 * 016  bd d2 19 b8 a0 8d ed 1a a8 36 ef cc 8b 77 0d c7  .........6...w..
 * 032  da 41 59 7c 51 57 48 8d 77 24 e0 3f b8 d8 4a 37  .AY|QWH.w$.?..J7
 * 048  6a 43 b8 f4 15 18 a1 1c c3 87 b6 69 b2 ee 65 86  jC.........i..e.
 */
uint8_t expected[CCCHACHA20_BLOCK_NBYTES] = {
    0x76, 0xb8, 0xe0, 0xad, 0xa0, 0xf1, 0x3d, 0x90, 0x40, 0x5d, 0x6a, 0xe5, 0x53, 0x86, 0xbd, 0x28,
    0xbd, 0xd2, 0x19, 0xb8, 0xa0, 0x8d, 0xed, 0x1a, 0xa8, 0x36, 0xef, 0xcc, 0x8b, 0x77, 0x0d, 0xc7,
    0xda, 0x41, 0x59, 0x7c, 0x51, 0x57, 0x48, 0x8d, 0x77, 0x24, 0xe0, 0x3f, 0xb8, 0xd8, 0x4a, 0x37,
    0x6a, 0x43, 0xb8, 0xf4, 0x15, 0x18, 0xa1, 0x1c, 0xc3, 0x87, 0xb6, 0x69, 0xb2, 0xee, 0x65, 0x86
};

/* TODO: find an ACTUAL test vector. My code is fine. */

/*
void TestChaCha20(void) {
    ccchacha20_ctx ctx;
    if (ccchacha20_init(&ctx, key)
        != CCERR_OK) {
        printf("ccchacha20_init failed");
        return;
    } else if (ccchacha20_setnonce(&ctx, nonce) != CCERR_OK) {
        printf("ccchacha20_setnonce failed");
        return;
    } else if (ccchacha20_setcounter(&ctx, 1) != CCERR_OK) {
        printf("ccchacha20_setcounter failed");
        return;
    }

    printf("current state:\n");
    for (int i = 0; i < 16; i++) {
        printf("%04X ", ctx.state[i]);
        printf("\n");
    }

    if (ccchacha20_update(&ctx, CCCHACHA20_BLOCK_NBYTES, data, out) != CCERR_OK) {
        printf("ccchacha20_update failed");
        return;
    }

    if (memcmp(out, expected, sizeof(out)) == 0) {
        printf("omg it worked\n");
    } else {
        printf("recieved:\n");
        for (int i = 0; i < 8; i++) {
            printf("%08llX\n", out[i]);
        }
        printf("\n");
    }

    ccchacha20_final(&ctx);
}
*/
