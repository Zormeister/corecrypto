//
//  ccaes_ctr.c
//  corecrypto
//
//  Created by Zormeister on 9/5/2025.
//

#include <corecrypto/ccaes.h>
#include <corecrypto/ccmode_impl.h>

/*
struct ccmode_ctr {
    size_t size;        -- first argument to ccctr_ctx_decl(). --
    size_t block_size;  -- for historical reasons, this is set to 1 --
    size_t ecb_block_size;  -- the actual block size of the underlying cipher --
    int (*init)(const struct ccmode_ctr *mode, ccctr_ctx *ctx,
                size_t key_len, const void *key, const void *iv);
    int (*setctr)(const struct ccmode_ctr *mode, ccctr_ctx *ctx, const void *ctr);
    int (*ctr)(ccctr_ctx *ctx, size_t nbytes, const void *in, void *out);
    const void *custom;
};
 */

/* ccaes_ctr_init */

struct ccaes_ctr_ctx {
    uint64_t counter[2]; /* first is for the IV, second is for the counter. */
};


int ccaes_ctr_init(const struct ccmode_ctr *mode, ccctr_ctx *ctx, size_t key_len, const void *key, const void *iv);

static struct ccmode_ctr ccaes_ctr_mode = {
    .size = sizeof(ccctr_ctx),
    .block_size = 1,
    .ecb_block_size = CCAES_BLOCK_SIZE,
    .init = ccaes_ctr_init,
};

const struct ccmode_ctr *ccaes_ctr_crypt_mode() { return &ccaes_ctr_mode; }
