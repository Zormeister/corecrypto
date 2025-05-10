//  Created by rafirafi on 3/17/16.
//  Copyright (c) 2016 rafirafi. All rights reserved.

#ifndef PDCRYPTO_DUMMY_H
#define PDCRYPTO_DUMMY_H

#include <corecrypto/ccdigest.h>
#include <corecrypto/cchmac.h>
#include <corecrypto/ccmode.h>
#include <corecrypto/ccrc4.h>
#include <corecrypto/ccrng.h>
#include <corecrypto/ccrsa.h>

extern const struct ccmode_xts pdcaes_xts_encrypt_dummy;
extern const struct ccmode_xts pdcaes_xts_decrypt_dummy;
extern const struct ccmode_gcm pdcaes_gcm_encrypt_dummy;
extern const struct ccmode_gcm pdcaes_gcm_decrypt_dummy;

extern const struct ccrc4_info pdcrc4_info_dummy;

extern const struct ccmode_ecb pdcblowfish_ecb_encrypt_dummy;
extern const struct ccmode_ecb pdcblowfish_ecb_decrypt_dummy;

extern const struct ccmode_ecb pdccast_ecb_encrypt_dummy;
extern const struct ccmode_ecb pdccast_ecb_decrypt_dummy;

void pdcdes_key_set_odd_parity_fn_dummy(void *key,
                                         unsigned long length);


void pdcpad_xts_decrypt_fn_dummy(const struct ccmode_xts *xts,
                                  ccxts_ctx *ctx,
                                  unsigned long nbytes,
                                  const void *in,
                                  void *out);

void pdcpad_xts_encrypt_fn_dummy(const struct ccmode_xts *xts,
                                  ccxts_ctx *ctx,
                                  unsigned long nbytes,
                                  const void *in,
                                  void *out);
#endif // PDCRYPTO_DUMMY_H
