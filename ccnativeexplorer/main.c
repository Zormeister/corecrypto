//
//  main.c
//  ccnativeexplorer
//
//  Created by Zormeister on 26/1/2025.
//

#include <stdio.h>
#include <corecrypto/ccdh.h>
#include <corecrypto/ccdh_gp.h>
#include <corecrypto/ccwrap.h>

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

uint8_t kek[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f};

uint8_t key[] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
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
    
    struct ccrng_state *rng = ccrng(NULL);
    
    uint64_t iv = 0;
    
    rng->generate(rng, 8, &iv);
    
    

    return 0;
}
