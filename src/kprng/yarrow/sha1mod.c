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

/*
SHA-1 in C
By Steve Reid <steve@edmweb.com>
100% Public Domain
*/
/* Header portion split from main code for convenience (AYB 3/02/98) */
#include "sha1mod.h"
#ifdef SHA1HANDSOFF
#include <string.h>
#endif

#define rol(value, bits) (((value) << (bits)) | ((value) >> (32 - (bits))))

/*
 * Apple change...
 */
#if defined(macintosh) || defined(__APPLE__)
#undef LITTLE_ENDIAN
#endif

/* blk0() and blk() perform the initial expand. */
/* I got the idea of expanding during the round function from SSLeay */
#ifdef LITTLE_ENDIAN
#define blk0(i) (block->l[i] = (rol(block->l[i], 24) & 0xFF00FF00) \
                     | (rol(block->l[i], 8) & 0x00FF00FF))
#else
#define blk0(i) block->l[i]
#endif
#define blk(i) (block->l[i & 15] = rol(block->l[(i + 13) & 15] ^ block->l[(i + 8) & 15] \
                                           ^ block->l[(i + 2) & 15] ^ block->l[i & 15], \
                                       1))

/* (R0+R1), R2, R3, R4 are the different operations used in SHA1 */
#define R0(v, w, x, y, z, i)                                     \
    z += ((w & (x ^ y)) ^ y) + blk0(i) + 0x5A827999 + rol(v, 5); \
    w = rol(w, 30);
#define R1(v, w, x, y, z, i)                                    \
    z += ((w & (x ^ y)) ^ y) + blk(i) + 0x5A827999 + rol(v, 5); \
    w = rol(w, 30);
#define R2(v, w, x, y, z, i)                            \
    z += (w ^ x ^ y) + blk(i) + 0x6ED9EBA1 + rol(v, 5); \
    w = rol(w, 30);
#define R3(v, w, x, y, z, i)                                          \
    z += (((w | x) & y) | (w & x)) + blk(i) + 0x8F1BBCDC + rol(v, 5); \
    w = rol(w, 30);
#define R4(v, w, x, y, z, i)                            \
    z += (w ^ x ^ y) + blk(i) + 0xCA62C1D6 + rol(v, 5); \
    w = rol(w, 30);

/* Hash a single 512-bit block. This is the core of the algorithm. */

__private_extern__ void
YSHA1Transform(u_int32_t state[5], const unsigned char buffer[64])
{
    u_int32_t a, b, c, d, e;
    typedef union {
        unsigned char c[64];
        u_int32_t l[16];
    } CHAR64LONG16;
    CHAR64LONG16 *block;
#ifdef SHA1HANDSOFF
    static unsigned char workspace[64];
    block = (CHAR64LONG16 *)workspace;
    memcpy(block, buffer, 64);
#else
    block = (CHAR64LONG16 *)buffer;
#endif
    /* Copy context->state[] to working vars */
    a = state[0];
    b = state[1];
    c = state[2];
    d = state[3];
    e = state[4];
    /* 4 rounds of 20 operations each. Loop unrolled. */
    R0(a, b, c, d, e, 0);
    R0(e, a, b, c, d, 1);
    R0(d, e, a, b, c, 2);
    R0(c, d, e, a, b, 3);
    R0(b, c, d, e, a, 4);
    R0(a, b, c, d, e, 5);
    R0(e, a, b, c, d, 6);
    R0(d, e, a, b, c, 7);
    R0(c, d, e, a, b, 8);
    R0(b, c, d, e, a, 9);
    R0(a, b, c, d, e, 10);
    R0(e, a, b, c, d, 11);
    R0(d, e, a, b, c, 12);
    R0(c, d, e, a, b, 13);
    R0(b, c, d, e, a, 14);
    R0(a, b, c, d, e, 15);
    R1(e, a, b, c, d, 16);
    R1(d, e, a, b, c, 17);
    R1(c, d, e, a, b, 18);
    R1(b, c, d, e, a, 19);
    R2(a, b, c, d, e, 20);
    R2(e, a, b, c, d, 21);
    R2(d, e, a, b, c, 22);
    R2(c, d, e, a, b, 23);
    R2(b, c, d, e, a, 24);
    R2(a, b, c, d, e, 25);
    R2(e, a, b, c, d, 26);
    R2(d, e, a, b, c, 27);
    R2(c, d, e, a, b, 28);
    R2(b, c, d, e, a, 29);
    R2(a, b, c, d, e, 30);
    R2(e, a, b, c, d, 31);
    R2(d, e, a, b, c, 32);
    R2(c, d, e, a, b, 33);
    R2(b, c, d, e, a, 34);
    R2(a, b, c, d, e, 35);
    R2(e, a, b, c, d, 36);
    R2(d, e, a, b, c, 37);
    R2(c, d, e, a, b, 38);
    R2(b, c, d, e, a, 39);
    R3(a, b, c, d, e, 40);
    R3(e, a, b, c, d, 41);
    R3(d, e, a, b, c, 42);
    R3(c, d, e, a, b, 43);
    R3(b, c, d, e, a, 44);
    R3(a, b, c, d, e, 45);
    R3(e, a, b, c, d, 46);
    R3(d, e, a, b, c, 47);
    R3(c, d, e, a, b, 48);
    R3(b, c, d, e, a, 49);
    R3(a, b, c, d, e, 50);
    R3(e, a, b, c, d, 51);
    R3(d, e, a, b, c, 52);
    R3(c, d, e, a, b, 53);
    R3(b, c, d, e, a, 54);
    R3(a, b, c, d, e, 55);
    R3(e, a, b, c, d, 56);
    R3(d, e, a, b, c, 57);
    R3(c, d, e, a, b, 58);
    R3(b, c, d, e, a, 59);
    R4(a, b, c, d, e, 60);
    R4(e, a, b, c, d, 61);
    R4(d, e, a, b, c, 62);
    R4(c, d, e, a, b, 63);
    R4(b, c, d, e, a, 64);
    R4(a, b, c, d, e, 65);
    R4(e, a, b, c, d, 66);
    R4(d, e, a, b, c, 67);
    R4(c, d, e, a, b, 68);
    R4(b, c, d, e, a, 69);
    R4(a, b, c, d, e, 70);
    R4(e, a, b, c, d, 71);
    R4(d, e, a, b, c, 72);
    R4(c, d, e, a, b, 73);
    R4(b, c, d, e, a, 74);
    R4(a, b, c, d, e, 75);
    R4(e, a, b, c, d, 76);
    R4(d, e, a, b, c, 77);
    R4(c, d, e, a, b, 78);
    R4(b, c, d, e, a, 79);
    /* Add the working vars back into context.state[] */
    state[0] += a;
    state[1] += b;
    state[2] += c;
    state[3] += d;
    state[4] += e;
    /* Wipe variables */
    a = b = c = d = e = 0;
}

/* YSHA1Init - Initialize new context */

__private_extern__ void
YSHA1Init(YSHA1_CTX *context)
{
    /* SHA1 initialization constants */
    context->state[0] = 0x67452301;
    context->state[1] = 0xEFCDAB89;
    context->state[2] = 0x98BADCFE;
    context->state[3] = 0x10325476;
    context->state[4] = 0xC3D2E1F0;
    context->count[0] = context->count[1] = 0;
}

/* Run your data through this. */

__private_extern__ void
YSHA1Update(YSHA1_CTX *context, const unsigned char *data, unsigned int len)
{
    unsigned int i, j;

    j = (context->count[0] >> 3) & 63;
    if ((context->count[0] += len << 3) < (len << 3)) {
        context->count[1]++;
    }
    context->count[1] += (len >> 29);
    if ((j + len) > 63) {
        memcpy(&context->buffer[j], data, (i = 64 - j));
        YSHA1Transform(context->state, context->buffer);
        for (; i + 63 < len; i += 64) {
            YSHA1Transform(context->state, &data[i]);
        }
        j = 0;
    } else {
        i = 0;
    }
    memcpy(&context->buffer[j], &data[i], len - i);
}

/* Add padding and return the message digest. */

__private_extern__ void
YSHA1Final(unsigned char digest[20], YSHA1_CTX *context)
{
    u_int32_t i, j;
    unsigned char finalcount[8];

    for (i = 0; i < 8; i++) {
        finalcount[i] = (unsigned char)((context->count[(i >= 4 ? 0 : 1)]
                                         >> ((3 - (i & 3)) * 8))
                                        & 255); /* Endian independent */
    }
    YSHA1Update(context, (const unsigned char *)"\200", 1);
    while ((context->count[0] & 504) != 448) {
        YSHA1Update(context, (const unsigned char *)"\0", 1);
    }
    YSHA1Update(context, finalcount, 8); /* Should cause a YSHA1Transform() */
    for (i = 0; i < 20; i++) {
        digest[i] = (unsigned char)((context->state[i >> 2] >> ((3 - (i & 3)) * 8)) & 255);
    }
    /* Wipe variables */
    i = j = 0;
    memset(context->buffer, 0, 64);
    memset(context->state, 0, 20);
    memset(context->count, 0, 8);
    memset(finalcount, 0, 8);
#ifdef SHA1HANDSOFF /* make YSHA1Transform overwrite it's own static vars */
    YSHA1Transform(context->state, context->buffer);
#endif
}

/*************************************************************/

/* Test Code */

#if 0

int main(int argc, char** argv)
{
int i, j;
YSHA1_CTX context;
unsigned char digest[20], buffer[16384];
FILE* file;

    if (argc > 2) {
        puts("Public domain SHA-1 implementation - by Steve Reid <steve@edmweb.com>");
        puts("Produces the SHA-1 hash of a file, or stdin if no file is specified.");
        exit(0);
    }
    if (argc < 2) {
        file = stdin;
    }
    else {
        if (!(file = fopen(argv[1], "rb"))) {
            fputs("Unable to open file.", stderr);
            exit(-1);
        }
    } 
    YSHA1Init(&context);
    while (!feof(file)) {  /* note: what if ferror(file) */
        i = fread(buffer, 1, 16384, file);
        YSHA1Update(&context, buffer, i);
    }
    YSHA1Final(digest, &context);
    fclose(file);
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 4; j++) {
            printf("%02X", digest[i*4+j]);
        }
        putchar(' ');
    }
    putchar('\n');
    exit(0);
}

#endif
