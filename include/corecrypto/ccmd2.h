//
//  ccmd2.h
//  corecrypto
//
//  Created by Zormeister on 25/1/2025.
//

#ifndef _CORECRYPTO_CCMD2_H_
#define _CORECRYPTO_CCMD2_H_

#include <corecrypto/ccdigest.h>

// MD2 interface

#define CCMD2_BLOCK_SIZE  16
#define CCMD2_OUTPUT_SIZE 16
#define CCMD2_STATE_SIZE  64

#define ccoid_md2 ((unsigned char *)"\x06\x08\x2A\x86\x48\x86\xF7\x0D\x02\x02")
#define ccoid_md2_len 10

// CommonCrypto uses the & operator on the digest function. I can only assume it returns the structure and not a pointer.

extern const struct ccdigest_info ccmd2_ltc_di;

// Apparently a macro???
// CommonCrypto uses it *like* one.
#define ccmd2_di ccmd2_ltc_di

#endif /* _CORECRYPTO_CCMD2_H_ */
