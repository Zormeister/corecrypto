//
//  ccsha3.h
//  corecrypto
//
//  Created by Zormeister on 29/11/2024.
//

#ifndef _CORECRYPTO_CCSHA3_H_
#define _CORECRYPTO_CCSHA3_H_

#include <corecrypto/ccdigest.h>

/* SHA-3 implementation, because we need that as of CommonCrypto from Darwin 20-ish */

const struct ccdigest_info *ccsha3_224_di(void);
const struct ccdigest_info *ccsha3_256_di(void);
const struct ccdigest_info *ccsha3_384_di(void);
const struct ccdigest_info *ccsha3_512_di(void);

/*
 * RESEARCH SOURCES:
 *  - https://datatracker.ietf.org/doc/rfc9688/
 */

/* Consult NIST FIPS 202 for more info */

/* See ccsha2.h for an explaination on the OIDs here */
#define ccoid_sha3_224 ((unsigned char *)"\x06\x09\x60\x86\x48\x01\x65\x03\x04\x02\x07")
#define ccoid_sha3_224_len 11

#define ccoid_sha3_256 ((unsigned char *)"\x06\x09\x60\x86\x48\x01\x65\x03\x04\x02\x08")
#define ccoid_sha3_256_len 11

#define ccoid_sha3_384 ((unsigned char *)"\x06\x09\x60\x86\x48\x01\x65\x03\x04\x02\x09")
#define ccoid_sha3_384_len 11

#define ccoid_sha3_512 ((unsigned char *)"\x06\x09\x60\x86\x48\x01\x65\x03\x04\x02\x0A")
#define ccoid_sha3_512_len 11

/* Thanks to my good old pal NM, I found out symbols for the C impls. */

#define CCSHA3_224_BLOCK_SIZE 144
#define CCSHA3_224_OUTPUT_SIZE 28
#define CCSHA3_224_STATE_SIZE 200
extern const struct ccdigest_info ccsha3_224_c_di;

#define CCSHA3_256_BLOCK_SIZE 136
#define CCSHA3_256_OUTPUT_SIZE 32
#define CCSHA3_256_STATE_SIZE 200
extern const struct ccdigest_info ccsha3_256_c_di;

#define CCSHA3_384_BLOCK_SIZE 104
#define CCSHA3_384_OUTPUT_SIZE 48
#define CCSHA3_384_STATE_SIZE 200
extern const struct ccdigest_info ccsha3_384_c_di;

#define CCSHA3_512_BLOCK_SIZE 72
#define CCSHA3_512_OUTPUT_SIZE 64
#define CCSHA3_512_STATE_SIZE 200
extern const struct ccdigest_info ccsha3_512_c_di;


#endif /* _CORECRYPTO_CCSHA3_H_ */
