//
//  ccdh_gp.h
//  corecrypto
//
//  Created by Zormeister on 26/1/2025.
//

#ifndef _CORECRYPTO_CCDH_GP_H_
#define _CORECRYPTO_CCDH_GP_H_

#include <corecrypto/ccdh.h>

ccdh_const_gp_t ccdh_gp_apple768(void);
ccdh_const_gp_t ccdh_gp_rfc2409group02(void);
ccdh_const_gp_t ccdh_gp_rfc3526group05(void);
ccdh_const_gp_t ccdh_gp_rfc3526group14(void);
ccdh_const_gp_t ccdh_gp_rfc3526group15(void);
ccdh_const_gp_t ccdh_gp_rfc3526group16(void);
ccdh_const_gp_t ccdh_gp_rfc3526group17(void);
ccdh_const_gp_t ccdh_gp_rfc3526group18(void);
ccdh_const_gp_t ccdh_gp_rfc5114_MODP_1024_160(void);
ccdh_const_gp_t ccdh_gp_rfc5114_MODP_2048_224(void);
ccdh_const_gp_t ccdh_gp_rfc5114_MODP_2048_256(void);

#endif /* _CORECRYPTO_CCDH_GP_H_ */
