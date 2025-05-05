//
//  ccec.h
//  corecrypto
//
//  Created by Zormeister on 8/2/2025.
//

#ifndef _CORECRYPTO_CCEC_H_
#define _CORECRYPTO_CCEC_H_

#include <corecrypto/cc.h>
#include <corecrypto/cczp.h>

// hunch based on the ccdh stuff
struct ccec_cp {
    __CCZP_ELEMENTS_DEFINITIONS()
} CC_ALIGNED(16);

typedef struct ccec_cp *ccec_cp_t;
typedef const struct ccec_cp *ccec_const_cp_t;

#define ccec_ccn_size(_cp_) 0

struct ccec_pub_ctx {

};

typedef struct ccec_pub_ctx *ccec_pub_ctx_t;

struct ccec_full_ctx {};

typedef struct ccec_pub_ctx *ccec_full_ctx_t;

#define ccec_pub_ctx_size(_size_) 0
#define ccec_full_ctx_size(_size_) 0

ccec_const_cp_t ccec_get_cp(size_t nbits);

bool ccec_keysize_is_supported(size_t nbits);

int ccec_sign(const void *key);

ccec_const_cp_t ccec_get_cp(size_t nbits);

int ccec_verify();

size_t ccec_ccn_size(ccec_const_cp_t cp);

#endif /* _CORECRYPTO_CCEC_H_ */
