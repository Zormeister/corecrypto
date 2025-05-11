//
//  ccec25519_priv.h
//  corecrypto
//
//  Created by Zormeister on 19/4/25.
//  Copyright © 2025 Zormeister. All rights reserved.
//

#ifndef _CORECRYPTO_CCEC25519_PRIV_H_
#define _CORECRYPTO_CCEC25519_PRIV_H_

#include <corecrypto/ccec25519.h>

/* various bits of SPI? */

void cccurve25519(ccec25519key out, const ccec25519secretkey secret, const ccec25519base);

#endif /* _CORECRYPTO_CCEC25519_PRIV_H_ */
