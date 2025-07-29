//
//  ccder_sizeof_oid.c
//  corecrypto
//
//  Created by Zormeister on 23/7/2025.
//

#include <corecrypto/ccder.h>

size_t ccder_sizeof_oid(ccoid_t oid)
{
    return ccoid_size(oid);
}
