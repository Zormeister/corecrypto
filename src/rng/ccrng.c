//
//  ccrng.c
//  corecrypto
//
//  Created by Zormeister on 9/5/2025.
//

#include <corecrypto/ccmode_impl.h>
#include <corecrypto/ccrng.h>
#include <corecrypto/ccaes.h>

/* CommonCrypto calls this RNG a DRBG. I assume this means the default RNG is actually the NIST CTR DRBG */
