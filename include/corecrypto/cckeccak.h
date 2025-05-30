//
//  cckeccak.h
//  corecrypto
//
//  Created by Zormeister on 27/5/2025.
//

#ifndef _CORECRYPTO_CCKECCAK_H_
#define _CORECRYPTO_CCKECCAK_H_

#include <corecrypto/cc.h>
#include <corecrypto/cc_config.h>

/* Grasping at straws here. */

/* 5 * 5 * 64 == 1600 */
struct cckeccak_state {
    uint64_t state[25];
};

typedef struct cckeccak_state *cckeccak_state_t;

#endif /* _CORECRYPTO_CCKECCAK_H_ */