//
//  cc_abort.c
//  corecrypto
//
//  Created by Zormeister on 8/7/25.
//

#include <corecrypto/cc_priv.h>
#include <corecrypto/cc_config.h>


//
// cc_abort
//

/* Should I define this as POSIX or STDC? tbh who cares. */
#define CC_POSIX (CC_LINUX || CC_OSX)

#if CC_POSIX

#include <stdlib.h>
#include <stdio.h>

void cc_abort(const char *msg) {
    fprintf(stderr, "%s\n", msg);
    abort();
}

#elif CC_KERNEL

#include <kern/debug.h>

void cc_abort(const char *msg) {
    panic("%s", msg);
}

#endif

