//
//  ccripemd.h
//  corecrypto
//
//  Created by Zormeister on 26/1/2025.
//

#ifndef _CORECRYPTO_CCRIPEMD_H_
#define _CORECRYPTO_CCRIPEMD_H_

#include <corecrypto/ccdigest.h>

#define CCRMD160_BLOCK_SIZE  64
#define CCRMD160_OUTPUT_SIZE 20
#define CCRMD160_STATE_SIZE  20

#define ccoid_rmd160 ((unsigned char *)"\x06\x05\x2B\x24\x03\x02\x01")
#define ccoid_rmd160_len 7

extern const struct ccdigest_info ccrmd160_ltc_di;

#define ccrmd160_di ccrmd160_ltc_di

#endif /* _CORECRYPTO_CCRIPEMD_H_ */
