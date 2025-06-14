//
//  ccmode_internal.h
//  corecrypto
//
//  Created by Zormeister on 13/6/2025.
//

#ifndef _CORECRYPTO_CCMODE_INTERNAL_H_
#define _CORECRYPTO_CCMODE_INTERNAL_H_

#include <corecrypto/ccmode.h>
#include <corecrypto/ccmode_factory.h>

/* CBC key positioning */
#define CCMODE_CBC_KEY_ECB_CTX(cbckey) (ccecb_ctx *)cbckey->u

/* CFB key fields */
#define CCMODE_CFB_KEY_FEEDBACK(ctx) ctx->u
/* ^ rename to IV? */
#define CCMODE_CFB_KEY_PADDING(ctx) (ctx->u + ccn_sizeof_size(ctx->ecb->block_size))
#define CCMODE_CFB_KEY_ECB_CTX(ctx) (ccecb_ctx *)ctx->u + (2 * ccn_sizeof_size(ctx->ecb->block_size))

/* CFB key fields */
#define CCMODE_CFB8_KEY_FEEDBACK(ctx) ctx->u
/* ^ rename to IV? */
#define CCMODE_CFB8_KEY_PADDING(ctx) (ctx->u + ccn_sizeof_size(ctx->ecb->block_size))
#define CCMODE_CFB8_KEY_ECB_CTX(ctx) (ccecb_ctx *)ctx->u + (2 * ccn_sizeof_size(ctx->ecb->block_size))

#define CCMODE_CTR_KEY_COUNTER(ckey) ckey->u
#define CCMODE_CTR_KEY_PAD(ckey) (ckey->u + ccn_sizeof_size(ckey->ecb->block_size))
#define CCMODE_CTR_KEY_ECB_CTX(ckey) (ccecb_ctx *)(ckey->u + ccn_sizeof_size(ckey->ecb->block_size) * 2)


#define CCMODE_OFB_KEY_IV(okey) okey->u
#define CCMODE_OFB_KEY_ECB_CTX(okey) (ccecb_ctx *)okey->u + ccn_sizeof_size(okey->ecb->block_size)

#endif /* _CORECRYPTO_CCMODE_INTERNAL_H_ */
