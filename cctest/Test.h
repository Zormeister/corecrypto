//
//  Test.h
//  corecrypto
//
//  Created by Zormeister on 25/1/2025.
//

#ifndef Test_h
#define Test_h

#include <stdint.h>

enum {
    kCCHashMD2 = 1,
    kCCHashMD4,
    kCCHashMD5,
    kCCHashRMD160,
    kCCHashSHA224,
    kCCHashSHA256,
    kCCHashSHA384,
    kCCHashSHA512,
};

typedef uint32_t CCTestHashAlgorithm;

struct {
    const char *in;
    size_t in_len;
    const uint32_t expected_out_len;
    const uint8_t *expected_out;
} typedef CCTestHashCase;


#endif /* Test_h */
