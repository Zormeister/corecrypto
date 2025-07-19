//
//  cchkdf_extract.c
//  corecrypto
//
//  Created by Zormeister on 7/5/2025.
//

#include <corecrypto/cchkdf.h>
#include <corecrypto/cchmac.h>

int cchkdf_extract(struct ccdigest_info *di, size_t salt_len, const void *salt, size_t ikm_len, const void *ikm, void *prk)
{
    if (salt == NULL) {
        uint8_t zero_salt[16] = { 0 };
        cchmac(di, 16, zero_salt, ikm_len, ikm, prk);
    } else {
        cchmac(di, salt_len, salt, ikm_len, ikm, prk);
    }
    return CCERR_OK;
}
