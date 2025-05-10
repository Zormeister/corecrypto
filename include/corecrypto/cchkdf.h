//
//  cchkdf.h
//  corecrypto
//
//  Created by Zormeister on 6/5/25.
//

#ifndef _CORECRYPTO_CCHKDF_H_
#define _CORECRYPTO_CCHKDF_H_

#include <corecrypto/ccdigest.h>

int cchkdf_extract(struct ccdigest_info *di,
                   size_t salt_len, const void *salt,
                   size_t ikm_len, const void *ikm,
                   void *prk);

int cchkdf_expand(struct ccdigest_info *di,
                  size_t prk_len, const void *prk,
                  size_t info_len, const void *info,
                  size_t derived_len, void *derived_key);

int cchkdf(struct ccdigest_info *di,
           size_t ikm_len, const void *ikm,
           size_t salt_len, const void *salt,
           size_t info_len, const void *info,
           size_t derived_len, void *derived_key);

#endif /* _CORECRYPTO_CCHKDF_H_ */
