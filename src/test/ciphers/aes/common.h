//
//  common.h
//  corecrypto
//
//  Created by Zormeister on 31/5/2025.
//  Copyright © 2025 William Kent. All rights reserved.
//

#ifndef common_h
#define common_h

#include <corecrypto/ccaes.h>

/* These are derived from the 128 Known Answer Test vectors provided by the NIST */
extern const uint8_t kAES128KnownAnswerTestKeys[CCAES_KEY_SIZE_128][128];
extern const uint8_t kAES128KnownAnswerTestInputs[CCAES_BLOCK_SIZE][128];

#endif /* common_h */
