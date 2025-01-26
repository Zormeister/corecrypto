//
//  ccmd4.h
//  corecrypto
//
//  Created by Zormeister on 26/1/2025.
//

#ifndef _CORECRYPTO_CCMD4_H_
#define _CORECRYPTO_CCMD4_H_

#include <corecrypto/ccdigest.h>

// MD4 interface

#define CCMD4_BLOCK_SIZE  64
#define CCMD4_OUTPUT_SIZE 16
#define CCMD4_STATE_SIZE  16

#define ccoid_md4 ((unsigned char *)"\x06\x08\x2A\x86\x48\x86\xF7\x0D\x02\x04")
#define ccoid_md4_len 10

extern const struct ccdigest_info ccmd4_ltc_di;

#define ccmd4_di ccmd4_ltc_di

#endif /* _CORECRYPTO_CCMD4_H_ */
