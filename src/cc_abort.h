#include <corecrypto/cc_config.h>

#if CC_KERNEL
#include <kern/debug.h>

static void cc_abort(const char *msg) {
    panic("%s", msg);
}

#else
#include <stdio.h>
#include <stdlib.h>

static void cc_abort(const char *msg) {
    fprintf(stderr, "%s", msg);
    abort();
}

#endif
