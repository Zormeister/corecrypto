//
//  ccecies.h
//  corecrypto
//
//  Created by Zormeister on 17/6/2025.
//

#ifndef _CORECRYPTO_CCECIES_H_
#define _CORECRYPTO_CCECIES_H_

#include <corecrypto/ccdigest.h>
#include <corecrypto/ccec.h>
#include <corecrypto/ccmode.h>

struct ccecies_gcm;

#define ECIES_EPH_PUBKEY_IN_SHAREDINFO1 0x1
#define ECIES_EXPORT_PUB_STANDARD 0x2
#define ECIES_LEGACY_IV 0x4

void ccecies_decrypt_gcm_setup(struct ccecies_gcm *ecies,
                               const struct ccdigest_info *di,
                               const struct ccmode_gcm *gcm,
                               size_t key_size, size_t unk,
                               uint32_t options);

void ccecies_encrypt_gcm_setup(struct ccecies_gcm *ecies,
                               const struct ccdigest_info *di,
                               const struct ccmode_gcm *gcm,
                               size_t key_size, size_t unk,
                               uint32_t options);

#endif /* _CORECRYPTO_CCECIES_H_ */
