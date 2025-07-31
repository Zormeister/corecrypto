/*
 *  cc_runtime_config.h
 *  corecrypto
 *
 *  Created on 09/18/2012
 *
 *  Copyright (c) 2012,2014,2015 Apple Inc. All rights reserved.
 *
 */

#ifndef CORECRYPTO_CC_RUNTIME_CONFIG_H_
#define CORECRYPTO_CC_RUNTIME_CONFIG_H_

#include <corecrypto/cc_config.h>

/* Only intel systems have these runtime switches today. */

#if defined(__x86_64__) || defined(__i386__)

#if CC_KERNEL
    #include <i386/cpuid.h>
    #define CC_HAS_RDRAND() ((cpuid_features() & CPUID_FEATURE_RDRAND) != 0)
#elif CC_XNU_KERNEL_AVAILABLE
    #include <System/i386/cpu_capabilities.h>

    extern int _cpu_capabilities;
    #define CC_HAS_RDRAND() (_cpu_capabilities & kHasRDRAND)
#else
    #define CC_HAS_RDRAND() 0
#endif

#if (CCSHA1_VNG_INTEL || CCSHA2_VNG_INTEL || CCAES_INTEL_ASM)

#if CC_KERNEL
    #include <i386/cpuid.h>
    #define CC_HAS_AESNI() ((cpuid_features() & CPUID_FEATURE_AES) != 0)
    #define CC_HAS_SupplementalSSE3() ((cpuid_features() & CPUID_FEATURE_SSSE3) != 0)
    #define CC_HAS_AVX1() ((cpuid_features() & CPUID_FEATURE_AVX1_0) != 0)
    #define CC_HAS_AVX2() ((cpuid_info()->cpuid_leaf7_features & CPUID_LEAF7_FEATURE_AVX2) != 0)
    #define CC_HAS_AVX512_AND_IN_KERNEL()    ((cpuid_info()->cpuid_leaf7_features & CPUID_LEAF7_FEATURE_AVX512F) !=0)
    #define CC_HAS_SHA()  ((cpuid_info()->cpuid_leaf7_features & CPUID_LEAF7_FEATURE_SHA) != 0)

#elif CC_XNU_KERNEL_AVAILABLE
    #include <System/i386/cpu_capabilities.h>

    extern int _cpu_capabilities;
    #define CC_HAS_AESNI() (_cpu_capabilities & kHasAES)
    #define CC_HAS_SupplementalSSE3() (_cpu_capabilities & kHasSupplementalSSE3)
    #define CC_HAS_AVX1() (_cpu_capabilities & kHasAVX1_0)
    #define CC_HAS_AVX2() (_cpu_capabilities & kHasAVX2_0)
    #define CC_HAS_AVX512_AND_IN_KERNEL() 0
#if defined(kHasSHA)
    //
    // ZORMEISTER:
    // So far I've implemented kHasSHA in my fork of XNU 6153.141.1,
    // (see https://github.com/Zormeister/xnu/tree/6153/x86-dev, as of commit a53a66fa63514b14d699767b273826010c2f3d2d)
    // This will likely have to be expanded in the future, so that
    // other clients of this corecrypto implementation can take
    // advantage of the SHA extensions on Intel.
    //
    #define CC_HAS_SHA() (_cpu_capabilities & kHasSHA)
#else
    #define CC_HAS_SHA() 0
#endif // defined(kHasSHA)

#elif __has_include(<cpuid.h>)
    #include <cpuid.h>

    //
    // ZORMEISTER:
    // I tried to take advantage of the available macros; but I don't
    // think I can cover everything without having to mess with
    // interacting with /proc/cpuinfo
    // Unless I use an external library or implement a parser for cpuinfo
    // and have an embedded function.
    //

    #define CC_HAS_AESNI() __builtin_cpu_supports("aes")
    #define CC_HAS_SupplementalSSE3() __builtin_cpu_supports("ssse3")
    #define CC_HAS_AVX1() __builtin_cpu_supports("avx")
    #define CC_HAS_AVX2() __builtin_cpu_supports("avx2")
    #define CC_HAS_AVX512_AND_IN_KERNEL() 0
    #define CC_HAS_SHA() 0

#elif __has_include(<immintrin.h>)
    #include <immintrin.h>
    #define CC_HAS_AESNI() _may_i_use_cpu_feature(_FEATURE_AES)
    #define CC_HAS_SupplementalSSE3() _may_i_use_cpu_feature(_FEATURE_SSSE3)
    #define CC_HAS_AVX1() _may_i_use_cpu_feature(_FEATURE_AVX)
    #define CC_HAS_AVX2() _may_i_use_cpu_feature(_FEATURE_AVX2)
    #define CC_HAS_AVX512_AND_IN_KERNEL()  0
    #define CC_HAS_SHA() _may_i_use_cpu_feature(_FEATURE_SHA)

#else
    #define CC_HAS_AESNI() 0
    #define CC_HAS_SupplementalSSE3() 0
    #define CC_HAS_AVX1() 0
    #define CC_HAS_AVX2() 0
    #define CC_HAS_AVX512_AND_IN_KERNEL()  0
    #define CC_HAS_SHA() 0

#endif

#endif  // (CCSHA1_VNG_INTEL || CCSHA2_VNG_INTEL || CCAES_INTEL_ASM)

#endif  // defined(__x86_64__) || defined(__i386__)

#endif /* CORECRYPTO_CC_RUNTIME_CONFIG_H_ */
