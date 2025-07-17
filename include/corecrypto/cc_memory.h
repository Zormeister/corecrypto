//
//  cc_memory.h
//  corecrypto
//
//  Created by Zormeister on 10/7/2025.
//

#ifndef _CORECRYPTO_CC_MEMORY_H_
#define _CORECRYPTO_CC_MEMORY_H_

#include <corecrypto/cc_config.h>
#include <corecrypto/ccn.h>

/* Workspace related macros go here. */

#if CC_USE_HEAP_FOR_WORKSPACE

#if CC_KERNEL

/* Use IOKit's memory allocation services. */

#include <IOKit/IOLib.h>

#define CC_WS_ALLOC_N(ws, n) \
            cc_ws ws##_ctx; \
            cc_ws_t ws = &ws##_ctx; \
            ws->start = IOMalloc(ccn_sizeof_n(n)); \
            ws->end = ws->start + ccn_sizeof_n(n); \

#define CC_WS_FREE_N(ws, n) \
            IOFree(ws->start, ccn_sizeof_n(n)); \
            ws->end = NULL; \

#define CC_WS_ALLOC(ws, size) \
            cc_ws ws##_ctx; \
            cc_ws_t ws = &ws##_ctx; \
            ws->start = IOMalloc(size); \
            ws->end = ws.start + size; \

#define CC_WS_FREE(ws, size) \
            IOFree(ws->start, size); \
            ws->end = NULL; \

#else

/* Linux, Windows, darwinOS, etc. */

#include <stdlib.h>

#define CC_WS_ALLOC_N(ws, n) \
            cc_ws ws##_ctx; \
            cc_ws_t ws = &ws##_ctx; \
            ws->start = malloc(ccn_sizeof_n(n)); \
            ws->end = ws->start + ccn_sizeof_n(n); \

#define CC_WS_FREE_N(ws, n) \
            free(ws->start); \
            ws->start = NULL; \
            ws->end = NULL; \

#define CC_WS_ALLOC(ws, size) \
            cc_ws ws##_ctx; \
            cc_ws_t ws = &ws##_ctx; \
            ws->start = malloc(size); \
            ws->end = ws->start + size; \

#define CC_WS_FREE(ws, size) \
            free(ws->start); \
            ws->end = NULL; \

#endif

#else

#define CC_WS_ALLOC_N(ws, n) \
            cc_unit ws##_buf[n]; \
            cc_ws ws##_ctx; \
            cc_ws_t ws = &ws##_ctx; \
            ws->start = &ws##_buf; \
            ws->end = ws->start + ccn_sizeof_n(n); \

#define CC_WS_FREE_N(ws, n) \
            ccn_clear(ws->start, n); \
            ws->start = NULL; \
            ws->end = NULL; \

#define CC_WS_ALLOC(ws, size) \
            uint8_t ws##_buf[size]; \
            cc_ws ws##_ctx; \
            cc_ws_t ws = &ws##_ctx; \
            ws->start = malloc(size); \
            ws->end = ws->start + size; \

#define CC_WS_FREE(ws, size) \
            cc_clear(ws->start, size); \
            ws->start = NULL; \
            ws->end = NULL; \

#endif /* CC_USE_HEAP_FOR_WORKSPACE */

#endif /* _CORECRYPTO_CC_MEMORY_H_ */
