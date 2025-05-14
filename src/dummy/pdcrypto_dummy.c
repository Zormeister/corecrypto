#include "pdcrypto_dummy.h"

#if KERNEL
#include <sys/systm.h>
#else
#include <stdio.h>
#endif

#include <corecrypto/ccdigest.h>

/*
 * to print what is used by xnu during boot
 */

static int pdcmode_ecb_init_dummy(const struct ccmode_ecb *ecb, ccecb_ctx *ctx,
                                   size_t key_len, const void *key)
{
    printf("%s\n", __func__);
	return -1;
}

const struct ccmode_xts pdcaes_xts_encrypt_dummy;
const struct ccmode_xts pdcaes_xts_decrypt_dummy;
const struct ccmode_gcm pdcaes_gcm_encrypt_dummy;
const struct ccmode_gcm pdcaes_gcm_decrypt_dummy;

const struct ccrc4_info pdcrc4_info_dummy;


void pdcdes_key_set_odd_parity_fn_dummy(void *key,
                                        unsigned long length)
{
    printf("%s\n", __func__);
}

void pdcpad_xts_decrypt_fn_dummy(const struct ccmode_xts *xts,
                                 ccxts_ctx *ctx,
                                 unsigned long nbytes,
                                 const void *in,
                                 void *out)
{
    printf("%s\n", __func__);
}

void pdcpad_xts_encrypt_fn_dummy(const struct ccmode_xts *xts,
                                 ccxts_ctx *ctx,
                                 unsigned long nbytes,
                                 const void *in,
                                 void *out)
{
    printf("%s\n", __func__);
}
