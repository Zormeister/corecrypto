//
//  cchkdf_expand.c
//  corecrypto
//
//  Created by Zormeister on 7/5/2025.
//

#include <corecrypto/cchkdf.h>
#include <corecrypto/cchmac.h>

int cchkdf_expand(struct ccdigest_info *di, size_t prk_len, const void *prk,
                  size_t info_len, const void *info,
                  size_t derived_len, void *derived_key)
{
    /* TODO */
    return CCERR_OK;
}
