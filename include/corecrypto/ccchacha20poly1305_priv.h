/*
 * Copyright (C) 2025 Zormeister and The PureDarwin project, All rights reserved.
 *
 * @LICENSE_HEADER_BEGIN@
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * @LICENSE_HEADER_END@
 */

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

int ccpoly1305_final(ccpoly1305_ctx *ctx, void *tag);

/*
 000000000006fa68 T _ccpoly1305
 000000000006f7f2 T _ccpoly1305_final
 000000000006f145 T _ccpoly1305_init
 000000000006f24f T _ccpoly1305_update
 */

#endif
