//
//  ccchacha20poly1305_priv.h
//  corecrypto
//
//  Created by Zormeister on 11/2/2025.
//

#ifndef _CORECRYPTO_CCCHACHA20POLY1305_PRIV_H_
#define _CORECRYPTO_CCCHACHA20POLY1305_PRIV_H_

#include <corecrypto/ccchacha20poly1305.h>

// i assume this just runs the ChaCha20 cipher on the in data.
int ccchacha20(const void *key, const void *nonce, uint32_t counter, size_t nbytes, const void *in, void *out);

#endif
