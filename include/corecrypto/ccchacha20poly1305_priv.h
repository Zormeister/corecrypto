//
//  ccchacha20poly1305_priv.h
//  corecrypto
//
//  Created by Zormeister on 11/2/2025.
//

#ifndef _CORECRYPTO_CCCHACHA20POLY1305_PRIV_H_
#define _CORECRYPTO_CCCHACHA20POLY1305_PRIV_H_

#include <corecrypto/cc.h>
#include <corecrypto/ccchacha20poly1305.h>

// i assume this just runs the ChaCha20 cipher on the in data.
int ccchacha20(const void *key, const void *nonce, uint32_t counter, size_t nbytes, const void *in, void *out);

// guess work on internal functions, after having reviewed the functions in chacha20poly1305.h

// probing says yes
int ccchacha20_init(ccchacha20_ctx *ctx, const uint8_t *key);
// probing says yes
int ccchacha20_setcounter(ccchacha20_ctx *ctx, uint32_t counter);
// probing says yes
int ccchacha20_setnonce(ccchacha20_ctx *ctx, const uint8_t *nonce);

// Took a lil' analysis, figured out that it was different due to the throwing of a bus error after param 3 was set to 64 (CCCHACHA20_BLOCK_NBYTES),
// then I had to try and figure out the segmentation faults.
// Why the shit doesn't it check the parameters though? That seems a bit stupid.
int ccchacha20_update(ccchacha20_ctx *ctx, size_t nbytes, const void *in, void *out);

int ccchacha20_final(ccchacha20_ctx *ctx);

int ccchacha20_reset(ccchacha20_ctx *ctx);

/* poly1305 */

/* confirmed. */
int ccpoly1305_init(ccpoly1305_ctx *ctx, const uint8_t *key);

/* Going off of the ChaCha20 sigs, I'll just do this... */
int ccpoly1305_update(ccpoly1305_ctx *ctx, size_t nbytes, const void *in);

/* ok so we need to get the tag somehow. lemme probe */
int ccpoly1305_final(ccpoly1305_ctx *ctx, void *tag);

/*
 000000000006fa68 T _ccpoly1305
 000000000006f7f2 T _ccpoly1305_final
 000000000006f145 T _ccpoly1305_init
 000000000006f24f T _ccpoly1305_update
 */

#endif
