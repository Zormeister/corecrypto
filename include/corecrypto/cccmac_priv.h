//
//  ccmac_priv.h
//  corecrypto
//
//  Created by Zormeister on 12/4/25.
//

#ifndef _CORECRYPTO_CCCMAC_PRIV_H_
#define _CORECRYPTO_CCCMAC_PRIV_H_

#include <corecrypto/cccmac.h>

int cccmac_generate_subkeys(cccmac_ctx_t ctx, size_t key_nbytes, const void *key);

#endif /* _CORECRYPTO_CCCMAC_PRIV_H_ */
