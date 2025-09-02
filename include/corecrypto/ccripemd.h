/*
 * Copyright (C) 2025 Zormeister and The PureDarwin project, All rights reserved.
 *
 * @LICENSE_HEADER_BEGIN@
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * @LICENSE_HEADER_END@
 */

#ifndef _CORECRYPTO_CCRIPEMD_H_
#define _CORECRYPTO_CCRIPEMD_H_

#include <corecrypto/ccdigest.h>

#define CCRMD160_BLOCK_SIZE  64
#define CCRMD160_OUTPUT_SIZE 20
#define CCRMD160_STATE_SIZE  20

#define ccoid_rmd160 ((unsigned char *)"\x06\x05\x2B\x24\x03\x02\x01")
#define ccoid_rmd160_len 7

extern const struct ccdigest_info ccrmd160_ltc_di;

#define ccrmd160_di ccrmd160_ltc_di

#endif /* _CORECRYPTO_CCRIPEMD_H_ */
