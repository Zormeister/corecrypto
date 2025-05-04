//
//  cc_abort.h
//  corecrypto
//
//  Created by Zormeister on 4/5/25.
//

#ifndef _CORECRYPTO_CC_ABORT_H_
#define _CORECRYPTO_CC_ABORT_H_

#include <corecrypto/cc_config.h>

#if CC_KERNEL
#include <kern/debug.h>

static void cc_abort(const char *msg) {
    panic("%s", msg);
}

#elif CC_OSX || CC_IOS || CC_LINUX

#include <stdio.h>
#include <stdlib.h>

static void cc_abort(const char *msg) {
    fprintf(stderr, "%s", msg);
    abort();
}

#endif

#endif /* _CORECRYPTO_CC_ABORT_H_ */
