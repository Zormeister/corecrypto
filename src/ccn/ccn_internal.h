//
//  ccn_internal.h
//  corecrypto
//
//  Created by Zormeister on 15/6/2025.
//

#ifndef _CORECRYPTO_CCN_INTERNAL_H_
#define _CORECRYPTO_CCN_INTERNAL_H_

#include <corecrypto/ccn.h>

/* ASM stuff... */
cc_unit ccn_add_asm(cc_size n, cc_unit *r, const cc_unit *s, const cc_unit *t);
cc_unit ccn_sub_asm(cc_size n, cc_unit *r, const cc_unit *s, const cc_unit *t);

#endif /* _CORECRYPTO_CCN_INTERNAL_H_ */
