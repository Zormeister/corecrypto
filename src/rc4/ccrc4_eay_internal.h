//
//  ccrc4_eay_internal.h
//  corecrypto
//
//  Created by Zormeister on 23/5/2025.
//

#ifndef _CORECRYPTO_CCRC4_EAY_INTERNAL_H_
#define _CORECRYPTO_CCRC4_EAY_INTERNAL_H_

#include <corecrypto/ccrc4.h>

typedef uint32_t RC4_INT;

/* and we'll map to unique function names to avoid collisions with libcrypto */
#define RC4_set_key	eay_RC4_set_key
#define RC4			eay_RC4

#define RC4_MIN_KEY_SIZE_BYTES	1
#define RC4_MAX_KEY_SIZE_BYTES	512

typedef struct rc4_key_st
	{
	RC4_INT x,y;
	RC4_INT data[256];
} RC4_KEY;

void RC4_set_key(RC4_KEY *key, int len, const unsigned char *data);
void RC4(RC4_KEY *key, unsigned long len, const unsigned char *indata,
		unsigned char *outdata);

#endif /* _CORECRYPTO_CCRC4_EAY_INTERNAL_H_ */
