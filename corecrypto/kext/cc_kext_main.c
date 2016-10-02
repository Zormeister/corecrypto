#include <mach/mach_types.h>
#include <kern/debug.h>
#include <libkern/crypto/register_crypto.h>
#include <mbedtls/aes.h>

static struct mbedtls_functions cc_mbedtls_functions = {
	mbedtls_aes_init,
	mbedtls_aes_free,
	mbedtls_aes_setkey_enc,
	mbedtls_aes_setkey_dec,
	mbedtls_aes_crypt_cbc
};

kern_return_t cc_kext_start(kmod_info_t * ki, void *d)
{
	int success = register_mbedtls_callbacks(&cc_mbedtls_functions);
	if (success != 0) panic("Could not register mbedTLS callbacks");
	return KERN_SUCCESS;
}

kern_return_t cc_kext_stop(kmod_info_t *ki, void *d)
{
	return KERN_FAILURE;
}
