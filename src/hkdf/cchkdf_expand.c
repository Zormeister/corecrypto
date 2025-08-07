//
//  cchkdf_expand.c
//  corecrypto
//
//  Created by Zormeister on 7/5/2025.
//

#include <corecrypto/cchkdf.h>
#include <corecrypto/cchmac.h>
#include <corecrypto/cc_priv.h>

//
// https://www.rfc-editor.org/rfc/rfc5869
// 
// 2.2 - Step 2: Expand
//

int cchkdf_expand(struct ccdigest_info *di, size_t prk_len, const void *prk,
                  size_t info_len, const void *info,
                  size_t derived_len, void *derived_key)
{
    uint8_t T[di->output_size];
    size_t n = cc_ceiling(derived_len, di->output_size);
    size_t Tlength = 0;
    size_t finalBytes = derived_len - (n * di->output_size);
    size_t finalBytesOffset = derived_len - finalBytes;
    cchmac_di_decl(di, hmac);
    cchmac_di_decl(di, hmac_initial);

    if (n > 255) {
        return CCERR_PARAMETER;
    } else if (prk_len < di->output_size) {
    
    }

    // i'm actually glad that HMAC ops can be split up into different function calls
    cchmac_init(di, hmac_initial, prk_len, prk);

    for (size_t i = 1; i <= n; i++) {
        uint8_t ctr = (uint8_t)i;

        cc_memcpy(hmac, hmac_initial, cchmac_di_size(di));

        // update using the contents of T first.
        cchmac_update(di, hmac, Tlength, T);

        // then; update using the info string
        cchmac_update(di, hmac, info_len, info);

        // and then do the 'counter' field.
        cchmac_update(di, hmac, 1, &ctr);

        // generate the MAC
        cchmac_final(di, hmac, T);

        // that is a piece of our key; copy to derived_key and 'push' the pointer forward
        if (i == n) {
            cc_memcpy(derived_key, T, finalBytes);
        } else {
            cc_memcpy(derived_key, T, di->output_size);
        }

        Tlength = di->output_size;

        derived_key += di->output_size;
    }

    cc_clear(cchmac_di_size(di), hmac);
    cc_clear(cchmac_di_size(di), hmac_initial);
    cc_clear(di->output_size, T);

    return CCERR_OK;
}
