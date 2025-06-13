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


#endif /* _CORECRYPTO_CCMODE_INTERNAL_H_ */
