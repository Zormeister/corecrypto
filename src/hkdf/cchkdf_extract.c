//
//  cchkdf_extract.c
//  corecrypto
//
//  Created by Zormeister on 7/5/2025.
//

#include <corecrypto/cchkdf.h>
#include <corecrypto/cchmac.h>
#include <corecrypto/cc_priv.h>

//
// https://www.rfc-editor.org/rfc/rfc5869
// 
// 2.2 - Step 1: Extract
//

int cchkdf_extract(struct ccdigest_info *di, size_t salt_len, const void *salt, size_t ikm_len, const void *ikm, void *prk)
{
    if (salt == NULL || salt_len == 0) {
        // "if not provided, it is set to a string of HashLen zeros."
        uint8_t zero_salt[di->output_size];

        cchmac(di, di->output_size, zero_salt, ikm_len, ikm, prk);
    } else {
        cchmac(di, salt_len, salt, ikm_len, ikm, prk);
    }

    return CCERR_OK;
}
