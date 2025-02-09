//
//  sizes.c
//  corecrypto
//
//  Created by Zormeister on 28/1/2025.
//

#include <corecrypto/ccaes.h>
#include <corecrypto/ccwrap.h>
#include <corecrypto/ccwrap_priv.h>
#include <corecrypto/cc_priv.h>
#include <corecrypto/cc.h>

// Wrapped Key includes the included wrapped IV.
// The formula is literally just key_len + CCWRAP_SEMIBLOCK as the IV is limited to being a 64-bit value.
size_t ccwrap_wrapped_size(size_t size) {
    return size + CCWRAP_SEMIBLOCK;
}

// The same applies here.
size_t ccwrap_unwrapped_size(size_t size) {
    // Avoid integer overflow
    if (size < CCWRAP_SEMIBLOCK) {
        return 0;
    }
    return size - CCWRAP_SEMIBLOCK;
}

