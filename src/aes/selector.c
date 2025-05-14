//
//  selector.c
//  corecrypto
//
//  Created by Zormeister on 4/5/2025.
//

#include <corecrypto/ccaes.h>
#include <corecrypto/ccmode_impl.h>
#include <corecrypto/cc_runtime_config.h>

extern const struct ccmode_cbc pdcaes_cbc_encrypt;
extern const struct ccmode_cbc pdcaes_cbc_decrypt;
extern const struct ccmode_ecb pdcaes_ecb_encrypt;
extern const struct ccmode_ecb pdcaes_ecb_decrypt;

#if CC_LINUX_ASM
extern const struct ccmode_cbc ccaes_intel_cbc_encrypt_aesni_mode;
extern const struct ccmode_cbc ccaes_intel_cbc_decrypt_aesni_mode;
extern const struct ccmode_ecb ccaes_intel_ecb_encrypt_aesni_mode;
extern const struct ccmode_ecb ccaes_intel_ecb_decrypt_aesni_mode;
#endif

const struct ccmode_ecb *ccaes_ecb_encrypt_mode(void) {

#if CCAES_INTEL_ASM
    if (CC_HAS_AESNI()) {
        return &ccaes_intel_ecb_encrypt_aesni_mode;
    }
#endif

    return &pdcaes_ecb_encrypt;
};

const struct ccmode_ecb *ccaes_ecb_decrypt_mode(void) {

#if CCAES_INTEL_ASM
    if (CC_HAS_AESNI()) {
        return &ccaes_intel_ecb_decrypt_aesni_mode;
    }
#endif

    return &pdcaes_ecb_decrypt;
};

const struct ccmode_cbc *ccaes_cbc_encrypt_mode(void) {

#if CCAES_INTEL_ASM
    if (CC_HAS_AESNI()) {
        return &ccaes_intel_cbc_encrypt_aesni_mode;
    }
#endif

    return &pdcaes_cbc_encrypt;
};

const struct ccmode_cbc *ccaes_cbc_decrypt_mode(void) {

#if CCAES_INTEL_ASM
    if (CC_HAS_AESNI()) {
        return &ccaes_intel_cbc_decrypt_aesni_mode;
    }
#endif

    return &pdcaes_cbc_decrypt;
};
