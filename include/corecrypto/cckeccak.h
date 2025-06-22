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

/*
 000000000001e870 T _cckeccak_absorb_and_pad
 000000000001e805 T _cckeccak_absorb_blocks
 000000000001ea5c T _cckeccak_absorb_iovec
 000000000001e072 T _cckeccak_f1600_c
 000000000001ea38 T _cckeccak_get_permutation
 000000000001e7f3 T _cckeccak_init_state
 000000000001eda5 T _cckeccak_oneshot
 000000000001ecba T _cckeccak_oneshot_iovec
 000000000001e953 T _cckeccak_squeeze
 */

#endif /* _CORECRYPTO_CCKECCAK_H_ */
