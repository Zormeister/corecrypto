//
//  main.c
//  ccnativeexplorer
//
//  Created by Zormeister on 26/1/2025.
//

#include <stdio.h>
#include <stdlib.h>
#include <corecrypto/ccdh.h>
#include <corecrypto/ccdh_gp.h>
#include <corecrypto/ccwrap.h>
#include <corecrypto/ccxof.h>
#include <corecrypto/cc.h>
#include <corecrypto/ccchacha20poly1305_priv.h>

void dump_dh_gp(ccdh_const_gp_t gp) {
    const uint8_t *ptr = (const uint8_t *)gp;
    for (int i = 0; i < 256; i++) {
        printf("%02X ", ptr[i]);
    }
    printf("\n");
    
    printf("\n");
    printf("size: %zu\n", gp->n);
    printf("bits: %lld\n", gp->options);
    printf("func: <%p>\n", gp->mulmod_prime);
}

void dump_xof(const struct ccxof_info *xof) {
    printf("xof: <%p>", xof);
    const uint8_t *ptr = (const uint8_t *)xof;
    for (int i = 0; i < 64; i++) {
        printf("%02X ", ptr[i]);
    }
}

uint8_t key[32] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1};
uint32_t nonce[3] = {0,0,0};

uint64_t data[8] = {0,0,0,0,0,0,0,0};

uint64_t out[8] = {0,0,0,0,0,0,0,0};
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

void probe_chacha(void) {

    ccchacha20(key, nonce, 1, CCCHACHA20_BLOCK_NBYTES, data, out);
    

/*  ccchacha20_ctx *ctx = malloc(sizeof(ccchacha20_ctx));
    if (ccchacha20_init(ctx, key)
        != CCERR_OK) {
        printf("ccchacha20_init failed");
        free(ctx);
        abort();
    } else if (ccchacha20_setnonce(ctx, (const uint8_t *)nonce) != CCERR_OK) {
        printf("ccchacha20_setnonce failed");
        free(ctx);
        abort();
    } else if (ccchacha20_setcounter(ctx, 1) != CCERR_OK) {
        printf("ccchacha20_setcounter failed");
        free(ctx);
        abort();
    }
        
    printf("current state:\n");
    for (int i = 0; i < 16; i++) {
        printf("%04X ", ctx->state[i]);
        printf("\n");
    }
    
    if (ccchacha20_update(ctx, CCCHACHA20_BLOCK_NBYTES, data, out) != CCERR_OK) {
        printf("ccchacha20_update failed");
        free(ctx);
        abort();
    }
    
    printf("post-update state:\n");
    for (int i = 0; i < 16; i++) {
        printf("%04X ", ctx->state[i]);
        printf("\n");
    }
    
    printf("post-update buffer:\n");
    for (int i = 0; i < CCCHACHA20_BLOCK_NBYTES; i++) {
        printf("%04X ", ctx->buffer[i]);
    }
    printf("\n");
*/
    if (memcmp(out, expected, sizeof(out)) == 0) {
        printf("ran the cipher\n");
        printf("recieved:\n");
        for (int i = 0; i < 8; i++) {
            printf("%08llX\n", out[i]);
        }
        printf("\n");
    } else {
        printf("recieved:\n");
        for (int i = 0; i < 8; i++) {
            printf("%08llX\n", out[i]);
        }
        printf("\n");
    }
/*
    if (ccchacha20_reset(ctx) != CCERR_OK) {
        printf("ccchacha20_reset failed");
        free(ctx);
        abort();
    }
    
    printf("post-reset state:\n");
    for (int i = 0; i < 16; i++) {
        printf("%04X ", ctx->state[i]);
        printf("\n");
    }
    printf("\n");
    
    printf("post-reset buffer:\n");
    for (int i = 0; i < CCCHACHA20_BLOCK_NBYTES; i++) {
        printf("%04X ", ctx->buffer[i]);
    }
    printf("\n");
    
    ccchacha20_final(ctx);
    
    printf("post-final state:\n");
    for (int i = 0; i < 16; i++) {
        printf("%04X ", ctx->state[i]);
        printf("\n");
    }
    printf("\n");
    
    printf("post-final buffer:\n");
    for (int i = 0; i < CCCHACHA20_BLOCK_NBYTES; i++) {
        printf("%04X ", ctx->buffer[i]);
    }
    printf("\n");
    
    free(ctx);
 */
}

/*
uint8_t kek[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f};

uint8_t key[] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};
 */

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    /*
    dump_dh_gp(ccdh_gp_apple768());
    dump_dh_gp(ccdh_gp_rfc2409group02());
    dump_dh_gp(ccdh_gp_rfc3526group05());
    dump_dh_gp(ccdh_gp_rfc3526group14());
    dump_dh_gp(ccdh_gp_rfc3526group15());
    dump_dh_gp(ccdh_gp_rfc3526group16());
    dump_dh_gp(ccdh_gp_rfc3526group17());
    dump_dh_gp(ccdh_gp_rfc3526group18());
    dump_dh_gp(ccdh_gp_rfc5114_MODP_1024_160());
    dump_dh_gp(ccdh_gp_rfc5114_MODP_2048_224());
    dump_dh_gp(ccdh_gp_rfc5114_MODP_2048_256());
    
    printf("\n");
    printf("Wrapped AES 128 Key Size: %zu\n", ccwrap_wrapped_size(CCAES_KEY_SIZE_128));
    printf("Wrapped AES 192 Key Size: %zu\n", ccwrap_wrapped_size(CCAES_KEY_SIZE_192));
    printf("Wrapped AES 256 Key Size: %zu\n", ccwrap_wrapped_size(CCAES_KEY_SIZE_256));
    printf("Invalid AES Key Size: %zu\n", ccwrap_wrapped_size(18));
     */
    
    //dump_xof(ccshake128_xi());
    //dump_xof(ccshake256_xi());

    
    probe_chacha();
    return 0;
}
