//
//  ccdh.h
//  corecrypto
//
//  Created by Zormeister on 26/1/2025.
//

#ifndef _CORECRYPTO_CCDH_H_
#define _CORECRYPTO_CCDH_H_

#include <corecrypto/cczp.h>
#include <corecrypto/ccrng.h>

// Something about 'sructures such as ccdh_gp_decl_n' has me a bit curious as to whether the GPs are actually just CCZPs
// That and the whole layout looks extremely similar.
struct ccdh_gp {
    __CCZP_ELEMENTS_DEFINITIONS()
} CC_ALIGNED(16);

#define ccdh_gp_n(gp) gp->n

typedef struct ccdh_gp *ccdh_gp_t;
typedef const struct ccdh_gp *ccdh_const_gp_t;

int ccdh_init_gp(ccdh_gp_t gp, cc_size n, cc_unit *p, cc_unit *g, cc_size l);

struct ccdh_pub_ctx {
    ccdh_const_gp_t gp;
};

typedef struct ccdh_pub_ctx *ccdh_pub_ctx_t;

struct ccdh_full_ctx {
    ccdh_const_gp_t gp;
};

typedef struct ccdh_full_ctx *ccdh_full_ctx_t;

int ccdh_generate_key(ccdh_const_gp_t gp, struct ccrng_state *rng, ccdh_full_ctx_t ctx);

int ccdh_import_pub(ccdh_const_gp_t gp, size_t pub_key_len, const void *pub_key, ccdh_pub_ctx_t pub);
void ccdh_export_pub(ccdh_pub_ctx_t ctx, void *out);

int ccdh_compute_shared_secret(ccdh_full_ctx_t ctx, ccdh_pub_ctx_t pub, size_t *shard_key_len, unsigned char *shared_key, struct ccrng_state *rng);

size_t ccdh_export_pub_size(ccdh_pub_ctx_t ctx);

#endif /* _CORECRYPTO_CCDH_H_ */
