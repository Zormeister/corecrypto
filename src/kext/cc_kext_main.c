#include <sys/systm.h>
#include <mach/mach_types.h>
#include "register_crypto.h"
#include "prng_random.h"
#include "../algorithms/cckprng.h"

extern struct crypto_functions pdcrypto_internal_functions;

kern_return_t cc_kext_start(kmod_info_t * ki, void *d)
{
	int ret = register_crypto_functions(&pdcrypto_internal_functions);
	if (ret == -1) {
		printf("warning: corecrypto could not be registered. Did another crypto handler beat us to it?\n");
	}

	struct prng_fns fns;
	fns.init = cckprng_init;
	fns.reseed = cckprng_reseed;
	fns.addentropy = cckprng_addentropy;
	fns.generate = cckprng_generate;
	register_and_init_prng(&fns);

	printf("corecrypto loaded\n");
    return KERN_SUCCESS;
}

kern_return_t cc_kext_stop(kmod_info_t *ki, void *d)
{
    return KERN_FAILURE;
}
