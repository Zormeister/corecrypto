//
//  ccansikdf.h
//  corecrypto
//
//  Created by Zormeister on 16/4/25.
//

#ifndef _CORECRYPTO_CCANSIKDF_H_
#define _CORECRYPTO_CCANSIKDF_H_

#include <corecrypto/ccdigest.h>

/*
 zormeister@Zormeisters-MacBook-Pro Sources % nm /usr/lib/system/libcorecrypto.dylib | grep ansikdf
    000000000004d5d8 T _ccansikdf_x963
    000000000004d4ee t _ccansikdf_x963_final
    000000000004d391 t _ccansikdf_x963_init
    000000000004d469 t _ccansikdf_x963_update
 */

int ccansikdf_x963(struct ccdigest_info *digest, size_t kdk_len, const void *kdk,
                   size_t sharedinfo_len, const void *sharedinfo,
                   size_t derived_len, void *derived_key);

#endif /* _CORECRYPTO_CCANSIKDF_H_ */
