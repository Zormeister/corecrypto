//
//  main.c
//  cctest
//
//  Created by Zormeister on 25/1/2025.
//

#include <stdio.h>
#include <corecrypto/cctest_priv.h>

#define CCTEST_MD2    0
#define CCTEST_MD4    0
#define CCTEST_RMD160 0

// fr gotta make more test cases
#if CCTEST_MD2
extern int TestMD2(void);
#endif
#if CCTEST_MD4
extern int TestMD4(void);
#endif
#if CCTEST_RMD160
extern int TestRMD160(void);
#endif

extern void TestChaCha20(void);

int main(int argc, const char *argv[])
{
    const struct cctest_info *ti = ccmd2_ti();
    cctest_ctx_decl(ti->size, md2);

    ti->init(ti, md2);

    if (ti->run(md2) == 0) {
        printf("lmao it worked");
    }

    return 0;
}
