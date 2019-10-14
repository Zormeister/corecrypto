//
//  cckprng.h
//  corecrypto_kernel
//
//  Created by William Kent on 10/14/19.
//  Copyright © 2019 William Kent. All rights reserved.
//

#ifndef __pdcrypto__cckprng__
#define __pdcrypto__cckprng__

#include <corecrypto/cckprng.h>

__BEGIN_DECLS

extern int cckprng_init(cckprng_ctx_t ctx, size_t nbytes, const void *seed);
extern int cckprng_reseed(cckprng_ctx_t ctx, size_t nbytes, const void *seed);
extern int cckprng_addentropy(cckprng_ctx_t ctx, size_t nbytes, const void *seed);
extern int cckprng_generate(cckprng_ctx_t ctx, size_t nbytes, void *out);

__END_DECLS

#endif /* __pdcrypto__cckprng__ */
