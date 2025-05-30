//
//  ccmac_priv.h
//  corecrypto
//
//  Created by Zormeister on 12/4/25.
//

#ifndef _CORECRYPTO_CCCMAC_PRIV_H_
#define _CORECRYPTO_CCCMAC_PRIV_H_

#include <corecrypto/cccmac.h>

int cccmac_generate_subkeys(const struct ccmode_cbc *cbc, size_t key_nbytes, const void *key, uint8_t *key1, uint8_t *key2);

#endif /* _CORECRYPTO_CCCMAC_PRIV_H_ */
