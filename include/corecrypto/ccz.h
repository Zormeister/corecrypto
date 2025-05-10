//
//  ccz.h
//  corecrypto
//
//  Created by Zormeister on 12/4/25.
//

#ifndef _CORECRYPTO_CCZ_H_
#define _CORECRYPTO_CCZ_H_

#include <stdbool.h>
#include <corecrypto/ccn.h>

struct ccz_class {
    void *ctx;
    void *(*ccz_alloc)(void *ctx, size_t size);
    void *(*ccz_realloc)(void *ctx, size_t oldsize, void *p, size_t newsize);
    void (*ccz_free)(void *ctx, size_t size, void *p);
};

struct {
    struct ccz_class ccz_class; /* I think? */
    uint64_t *z; /* Pointer to our large number - look at ccz_class for details. */
} typedef ccz;

void ccz_init(struct ccz_class *cl, ccz *r);

void ccz_free(ccz *z);

void ccz_zero(ccz *z);

size_t ccz_size(ccz *z);

size_t ccz_bitlen(ccz *z);

void ccz_set(ccz *r, const ccz *s);

bool ccz_is_one(ccz *z);

bool ccz_is_prime(ccz *z, size_t rounds);

bool ccz_is_negative(ccz *z);

bool ccz_is_zero(ccz *z);

#endif /* _CORECRYPTO_CCZ_H_ */
