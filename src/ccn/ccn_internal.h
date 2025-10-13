/*
 * Copyright (C) 2025 The PureDarwin Project, All rights reserved.
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

#ifndef _CORECRYPTO_CCN_INTERNAL_H_
#define _CORECRYPTO_CCN_INTERNAL_H_

#include <corecrypto/ccn.h>

/* ASM stuff... */
cc_unit ccn_add_asm(cc_size n, cc_unit *r, const cc_unit *s, const cc_unit *t);
cc_unit ccn_sub_asm(cc_size n, cc_unit *r, const cc_unit *s, const cc_unit *t);

#endif /* _CORECRYPTO_CCN_INTERNAL_H_ */
