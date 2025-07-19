#include <corecrypto/cc.h>
#include <stddef.h>

void cc_clear(size_t len, void *dst)
{
    // This implementation is taken from the mbedtls_zeroize() function in mbedtls/aes.c
    volatile unsigned char *p = dst;
    while (len--) {
        *p++ = 0;
    }
}
