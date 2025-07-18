//
//  selector.c
//  corecrypto
//
//  Created by Zormeister on 4/5/2025.
//

#include <corecrypto/cc_debug.h>
#include <corecrypto/cc_runtime_config.h>
#include <corecrypto/ccaes.h>
#include <corecrypto/ccmode_factory.h>
#include <corecrypto/ccmode_impl.h>

CCMODE_CFB_FACTORY(aes, cfb, encrypt)
CCMODE_CFB_FACTORY(aes, cfb, decrypt)
CCMODE_CFB_FACTORY(aes, cfb8, decrypt);
CCMODE_CFB_FACTORY(aes, cfb8, encrypt);

CCMODE_CTR_FACTORY(aes);

CCMODE_OFB_FACTORY(aes);

#if CC_LINUX_ASM
extern const struct ccmode_cbc ccaes_intel_cbc_encrypt_aesni_mode;
extern const struct ccmode_cbc ccaes_intel_cbc_decrypt_aesni_mode;
extern const struct ccmode_ecb ccaes_intel_ecb_encrypt_aesni_mode;
extern const struct ccmode_ecb ccaes_intel_ecb_decrypt_aesni_mode;
#endif

const struct ccmode_ecb *ccaes_ecb_encrypt_mode(void)
{

#if CCAES_INTEL_ASM
    if (CC_HAS_AESNI()) {
#if CORECRYPTO_DEBUG
        cc_printf("corecrypto(aes): using AES-NI for ECB encrypt\n");
#endif
        return &ccaes_intel_ecb_encrypt_aesni_mode;
    } else {
        return &ccaes_intel_ecb_encrypt_opt_mode;
    }
#endif

    return &ccaes_tinyaes_ecb_encrypt_mode;
};

const struct ccmode_ecb *ccaes_ecb_decrypt_mode(void)
{

#if CCAES_INTEL_ASM
    if (CC_HAS_AESNI()) {
#if CORECRYPTO_DEBUG
        cc_printf("corecrypto(aes): using AES-NI for ECB decrypt\n");
#endif
        return &ccaes_intel_ecb_decrypt_aesni_mode;
    } else {
        return &ccaes_intel_ecb_decrypt_opt_mode;
    }
#endif

    return &ccaes_tinyaes_ecb_decrypt_mode;
};

const struct ccmode_cbc *ccaes_cbc_encrypt_mode(void)
{

#if CCAES_INTEL_ASM
    if (CC_HAS_AESNI()) {
#if CORECRYPTO_DEBUG
        cc_printf("corecrypto(aes): using AES-NI for CBC encrypt\n");
#endif
        return &ccaes_intel_cbc_encrypt_aesni_mode;
    } else {
        return &ccaes_intel_cbc_encrypt_opt_mode;
    }
#endif

    return &ccaes_tinyaes_cbc_encrypt_mode;
};

const struct ccmode_cbc *ccaes_cbc_decrypt_mode(void)
{

#if CCAES_INTEL_ASM
    if (CC_HAS_AESNI()) {
#if CORECRYPTO_DEBUG
        cc_printf("corecrypto(aes): using AES-NI for CBC decrypt\n");
#endif
        return &ccaes_intel_cbc_decrypt_aesni_mode;
    } else {
        return &ccaes_intel_cbc_decrypt_opt_mode;
    }
#endif

    return &ccaes_tinyaes_cbc_decrypt_mode;
};
