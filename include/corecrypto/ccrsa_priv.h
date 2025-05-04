//
//  ccrsa_priv.h
//  corecrypto
//
//  Created by Zormeister on 4/5/25.
//

#ifndef _CORECRYPTO_CC_RSA_PRIV_H_
#define _CORECRYPTO_CC_RSA_PRIV_H_

#include <corecrypto/ccdigest.h>
#include <corecrypto/ccrng.h>
#include <corecrypto/ccrsa.h>

/* Various non-descript functions I've found. */

/* PKCS#1 v1.5 functions */
int ccrsa_encrypt_eme_pkcs1v15(ccrsa_pub_ctx_t pub,
                               struct ccdigest_info *digest,
                               struct ccrng_state *rng,
                               size_t ct_len, void *ct,
                               size_t pt_len, const void *pt,
                               size_t tag_len, const void *tag);

/* RSA OAEP functions. There's probably more I'm missing since I need my symbol dump. */
void ccrsa_oaep_encode(struct ccdigest_info *digest,
                       struct ccrng_state *rng,
                       size_t buffer_size, cc_unit *padding_buffer,
                       size_t data_len, const void *data);

int ccrsa_oaep_decode(struct ccdigest_info *digest,
                      size_t *plaintext_len, void *plaintext,
                      size_t msg_len, cc_unit *padding_buffer);

int ccrsa_encrypt_oaep(ccrsa_pub_ctx_t pub,
                       struct ccdigest_info *digest,
                       struct ccrng_state *rng,
                       size_t ct_len, void *ct,
                       size_t pt_len, const void *pt,
                       size_t tag_len, const void *tag);

#endif /* _CORECRYPTO_CC_RSA_PRIV_H */
