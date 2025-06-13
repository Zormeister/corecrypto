//
//  rsp2header.cpp
//  corecrypto
//
//  Created by Zormeister on 3/6/2025.
//

#include <string>
#include "lib/RSPParser.hpp"

using namespace CoreCrypto::RSP;

/* rsp2header hash -f <path/to/file> -o <path/to/out> */
/* rsp2header cipher -m cbc -f <path/to/vectors>.rsp -o <path/to/out>.h */

/* usually test vectors contain a DECRYPT and ENCRYPT tag in sections. it is up to RSPParser to handle this. */

const char *gRSPPath;
const char *gOutputPath;

Test::Operation gOp = Test::Operation::Hash; /* keep it like this for now */

void parse_args(int argc, const char *argv[]) {
    for (int i = 0; i < argc; i++) {
        std::string str = argv[i];
        if (str == "hash") {
            /* initialise parser context */
            gOp = Test::Operation::Hash
        } else if (str == "-f") {
            gRSPPath = str.c_str();
        } else if (str == "-o") {
            gOutputPath = str.c_str();
        }
    }
}

int main(int argc, const char *argv[]) {

}
