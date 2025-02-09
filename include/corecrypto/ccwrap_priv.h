//
//  ccwrap_priv.h
//  corecrypto
//
//  Created by Zormeister on 25/1/2025.
//

#ifndef _CORECRYPTO_CCWRAP_PRIV_H_
#define _CORECRYPTO_CCWRAP_PRIV_H_

// I have zero idea as to what pieces are supposed to be "private"
// So I made them all public. Womp womp.

#include <corecrypto/ccwrap.h>

// dunno.
int ccwrap_argsvalid(void);

extern const uint8_t ccwrap_default_iv[8]; // NOTE: This is NOT from any symbols in CoreCrypto. This is me doing my own thing here.

#endif /* _CORECRYPTO_CCWRAP_PRIV_H_ */
