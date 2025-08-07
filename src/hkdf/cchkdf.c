//
//  cchkdf.c
//  corecrypto
//
//  Created by Zormeister on 9/8/2025.
//

#include <corecrypto/cchkdf.h>
#include <corecrypto/cchmac.h>
#include <corecrypto/cc_priv.h>

int cchkdf(struct ccdigest_info *di, size_t ikm_len, const void *ikm, 
           size_t salt_len, const void *salt, 
           size_t info_len, const void *info, 
           size_t derived_len, void *derived_key)
{
    uint8_t prk[di->output_size];

    int res = cchkdf_extract(di, salt_len, salt, ikm_len, ikm, prk);
    if (res == CCERR_OK) {
        res = cchkdf_expand(di, di->output_size, prk, info_len, info, derived_len, derived_key);
    }

    cc_clear(di->output_size, prk);
    return res;
}
