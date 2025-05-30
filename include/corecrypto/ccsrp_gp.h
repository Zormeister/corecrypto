//
//  ccsrp_gp.h
//  corecrypto
//
//  Created by Zormeister on 22/5/2025.
//

#ifndef _CORECRYPTO_CCSRP_GP_H_
#define _CORECRYPTO_CCSRP_GP_H_

#include <corecrypto/ccsrp.h>

ccsrp_const_gp_t ccsrp_gp_rfc5054_1024(void);
ccsrp_const_gp_t ccsrp_gp_rfc5054_2048(void);
ccsrp_const_gp_t ccsrp_gp_rfc5054_3072(void);
ccsrp_const_gp_t ccsrp_gp_rfc5054_4096(void);
ccsrp_const_gp_t ccsrp_gp_rfc5054_8192(void);

#endif /* _CORECRYPTO_CCSRP_GP_H_ */
