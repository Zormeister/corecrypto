//
//  AESTest.c
//  cctest
//
//  Created by Zormeister on 4/5/2025.
//

#include <corecrypto/ccaes.h>

enum CIPHER_MODE {
    ECB,
    CBC,
};

struct AES_VECTOR {
    enum CIPHER_MODE Mode;
    size_t key_size;
    const uint8_t iv[16];
    const uint8_t key[32]; /* maximum key size is 256 bits. */
    size_t ct_size;
    size_t pt_size;
    const uint8_t *pt;
    const uint8_t *ct;
};

const uint8_t kAESTestPlaintext1[] = {0x6a, 0x84, 0x86, 0x7c, 0xd7, 0x7e, 0x12, 0xad, 0x07, 0xea, 0x1b, 0xe8, 0x95, 0xc5, 0x3f, 0xa3};

struct AES_VECTOR AES_VECTORS[] = {
    {
        ECB,
        CCAES_KEY_SIZE_128,
        {0},
        {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
        CCAES_BLOCK_SIZE,
        CCAES_BLOCK_SIZE,

    }
};

int TestAESECB() {

}
