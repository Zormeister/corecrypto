//
//  ccne_kext.c
//  ccne_kext
//
//  Created by Zormeister on 14/2/2025.
//

#include <mach/mach_types.h>
#include <pexpert/pexpert.h>
#include <corecrypto/ccxof.h>

void dump_xof(const struct ccxof_info *xof) {
    kprintf("[CCNE] === XOF <%p> ===", xof);
    const uint8_t *ptr = (const uint8_t *)xof;
    for (int i = 0; i < 64; i++) {
        kprintf("%02X ", ptr[i]);
    }
    kprintf("\n");
}

kern_return_t ccne_kext_start(kmod_info_t * ki, void *d);
kern_return_t ccne_kext_stop(kmod_info_t *ki, void *d);

kern_return_t ccne_kext_start(kmod_info_t * ki, void *d)
{
    dump_xof(ccshake128_xi());
    dump_xof(ccshake256_xi());
    return KERN_SUCCESS;
}

kern_return_t ccne_kext_stop(kmod_info_t *ki, void *d)
{
    return KERN_SUCCESS;
}
