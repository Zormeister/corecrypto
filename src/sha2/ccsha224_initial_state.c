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

#include "ccsha2_ltc_internal.h"

const uint32_t ccsha224_initial_state[8] = {
    0xc1059ed8UL,
    0x367CD507UL,
    0x3070dd17UL,
    0xf70e5939UL,
    0xffc00b31UL,
    0x68581511UL,
    0x64f98fa7UL,
    0xbefa4fa4UL,
};
