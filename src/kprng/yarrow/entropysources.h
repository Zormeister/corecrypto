/*
 * Copyright (c) 1999, 2000-2001 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_START@
 *
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. The rights granted to you under the License
 * may not be used to create, or enable the creation or redistribution of,
 * unlawful or unlicensed copies of an Apple operating system, or to
 * circumvent, violate, or enable the circumvention or violation of, any
 * terms of an Apple operating system software license agreement.
 *
 * Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this file.
 *
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_END@
 */

/* entropysources.h */
/* This files contain the defination of the entropy sources */

#ifndef __YARROW_ENTROPY_SOURCES_H__
#define __YARROW_ENTROPY_SOURCES_H__

#if defined(macintosh) || defined(__APPLE__)
/*
 * In our implementation, all sources are user sources.
 */
enum entropy_sources {
    ENTROPY_SOURCES = 0
};
#else
enum entropy_sources {
    KEYTIMESOURCE = 0,
    MOUSETIMESOURCE,
    MOUSEMOVESOURCE,
    SLOWPOLLSOURCE,
    ENTROPY_SOURCES, /* Leave as second to last source */
    MSG_CLOSE_PIPE   /* Leave as last source */
};
#endif

#endif
