//
//  cctest_digest_internal.h
//  corecrypto
//
//  Created by Zormeister on 31/5/2025.
//

#ifndef _CORECRYPTO_CCTEST_DIGEST_INTERNAL_H_
#define _CORECRYPTO_CCTEST_DIGEST_INTERNAL_H_

#include "../cctest_internal.h"
#include <corecrypto/cc.h>

#if CORECRYPTO_TEST

struct cctest_digest_vector {
    const char *message;
    const char *expected;
};

#endif /* CORECRYPTO_TEST */

#endif /* _CORECRYPTO_CCTEST_DIGEST_INTERNAL_H_ */