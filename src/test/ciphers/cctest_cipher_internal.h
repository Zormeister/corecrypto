//
//  cctest_cipher_internal.h
//  corecrypto
//
//  Created by Zormeister on 31/5/2025.
//

#ifndef _CORECRYPTO_CCTEST_CIPHER_INTERNAL_H_
#define _CORECRYPTO_CCTEST_CIPHER_INTERNAL_H_

#include <corecrypto/cc.h>

enum {
    crypto_op_enc,
    crypto_op_dec,
} typedef crypto_op_t;

struct cctest_cipher_vector {
    const char *key;
    const char *pt;
    const char *ct;
    const char *iv;
};

#endif /* _CORECRYPTO_CCTEST_CIPHER_INTERNAL_H_ */
