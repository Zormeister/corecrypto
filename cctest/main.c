//
//  main.c
//  cctest
//
//  Created by Zormeister on 25/1/2025.
//

#include <stdio.h>

#define CCTEST_MD2 1
#define CCTEST_MD4 1
#define CCTEST_RMD160 1

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

int main(int argc, const char * argv[]) {
    int res = -1;
#if CCTEST_MD2
    res |= TestMD2();
#endif

#if CCTEST_MD4
    res |= TestMD4();
#endif
    
#if CCTEST_RMD160
    res |= TestRMD160();
#endif
    return res;
}
