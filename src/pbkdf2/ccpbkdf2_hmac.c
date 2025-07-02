//
//  ccpbkdf2_hmac.c
//  corecrypto
//
//  Created by Zormeister on 30/6/2025.
//

#include "corecrypto/cc.h"
#include "corecrypto/cc_error.h"
#include "corecrypto/cc_priv.h"
#include "corecrypto/ccdigest_priv.h"
#include "corecrypto/ccn.h"
#include <corecrypto/ccpbkdf2.h>
#include <corecrypto/cchmac.h>

/*
 * read this for more info:
 * https://www.rfc-editor.org/rfc/rfc2898 
 */

int ccpbkdf2_hmac(const struct ccdigest_info *di, 
                  size_t passwordLen, const void *password, 
                  size_t saltLen, const void *salt, 
                  size_t iterations, 
                  size_t dkLen, void *dk) 
{
    size_t blocks = cc_ceiling(dkLen, di->output_size);
    int counter = 1;
    uint8_t block[di->output_size];
    uint8_t block2[di->output_size];
    cc_unit hmac_initial_state[ccn_nof_size(di->state_size)];
    cchmac_di_decl(di, hmac);
    cchmac_init(di, hmac, passwordLen, password);
    ccdigest_copy_state(di, hmac_initial_state, cchmac_istate(di, hmac));

    cc_try_abort("incomplete pbkdf2 impl\n");

    /* ZORMEISTER: Enforce requirements for the salt and derived key length. */
    if ((saltLen < 8) || (dkLen / di->output_size) > UINT32_MAX) {
        return CCERR_INTERNAL;
    }

    while (blocks--) {
        /* Compute U_1 */
        /* U_1 = PRF (P, S || INT (i)) , */
        cchmac_update(di, hmac, saltLen, salt);
        cchmac_update(di, hmac, sizeof(counter), &counter);
        cchmac_final(di, hmac, block);
        for (int i = 1; i < iterations; i++) {
            /* U_2 and subsequent blocks. */
            cchmac_update(di, hmac, di->output_size, cchmac_data(di, hmac));
            cchmac_final(di, hmac, cchmac_data(di, hmac));
            cc_xor(di->output_size, cchmac_data(di, hmac), block, block2);
        }
        /* This means we're done here and the block is computed. */
        if (dkLen < di->output_size) {
            cc_memcpy(dk, block, dkLen);
            break;
        } else {
            cc_memcpy(dk, block, di->output_size);
            dkLen -= di->output_size;
        }
        counter++;
    }

    return CCERR_OK;
}

