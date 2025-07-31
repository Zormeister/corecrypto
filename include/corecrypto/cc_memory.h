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

#define CC_WORKSPACE_STACK_DECL_N(ws, n) \
            cc_unit ws##_buf[ccn_sizeof_n(n)]; \
            cc_ws ws##_ctx; \
            cc_ws_t ws = &ws##_ctx; \
            ws->start = ws##_buf; \
            ws->end = ws->start + ccn_sizeof_n(n); \

#define CC_WORKSPACE_STACK_FREE_N(ws, n) \
            ccn_clear(n, ws->start); \
            ws->start = NULL; \
            ws->end = NULL; \

#define CC_WORKSPACE_STACK_DECL(ws, size) \
            uint8_t ws##_buf[size]; \
            cc_ws ws##_ctx; \
            cc_ws_t ws = &ws##_ctx; \
            ws->start = ws##_buf; \
            ws->end = ws->start + size; \

#define CC_WORKSPACE_STACK_FREE(ws, size) \
            cc_clear(size, ws->start); \
            ws->start = NULL; \
            ws->end = NULL; \

#if CC_USE_HEAP_FOR_WORKSPACE

#if CC_KERNEL

/* Use IOKit's memory allocation services. */

#include <IOKit/IOLib.h>

#define CC_WORKSPACE_DECL_N(ws, n) \
            cc_ws ws##_ctx; \
            cc_ws_t ws = &ws##_ctx; \
            ws->start = IOMalloc(ccn_sizeof_n(n)); \
            ws->end = ws->start + ccn_sizeof_n(n); \

#define CC_WORKSPACE_FREE_N(ws, n) \
            IOFree(ws->start, ccn_sizeof_n(n)); \
            ws->end = NULL; \

#define CC_WORKSPACE_DECL(ws, size) \
            cc_ws ws##_ctx; \
            cc_ws_t ws = &ws##_ctx; \
            ws->start = IOMalloc(size); \
            ws->end = ws.start + size; \

#define CC_WORKSPACE_FREE(ws, size) \
            IOFree(ws->start, size); \
            ws->end = NULL; \

#else

/* Linux, Windows, darwinOS, etc. */

#include <malloc.h>

#define CC_WORKSPACE_DECL_N(ws, n) \
            cc_ws ws##_ctx; \
            cc_ws_t ws = &ws##_ctx; \
            ws->start = malloc(ccn_sizeof_n(n)); \
            ws->end = ws->start + ccn_sizeof_n(n); \

#define CC_WORKSPACE_FREE_N(ws, n) \
            free(ws->start); \
            ws->start = NULL; \
            ws->end = NULL; \

#define CC_WORKSPACE_DECL(ws, size) \
            cc_ws ws##_ctx; \
            cc_ws_t ws = &ws##_ctx; \
            ws->start = malloc(size); \
            ws->end = ws->start + size; \

#define CC_WORKSPACE_FREE(ws, size) \
            free(ws->start); \
            ws->end = NULL; \

#endif

#else

#define CC_WORKSPACE_DECL_N(ws, n) CC_WORKSPACE_STACK_DECL_N(ws, n)

#define CC_WORKSPACE_FREE_N(ws, n) CC_WORKSPACE_STACK_FREE_N(ws, n)

#define CC_WORKSPACE_DECL(ws, size) CC_WORKSPACE_STACK_DECL(ws, n)

#define CC_WORKSPACE_FREE(ws, size) CC_WORKSPACE_STACK_FREE(ws, n)

#endif /* CC_USE_HEAP_FOR_WORKSPACE */

#endif /* _CORECRYPTO_CC_MEMORY_H_ */
