//
//  rsp2header.cpp
//  corecrypto
//
//  Created by Zormeister on 3/6/2025.
//

#include <string>

/* rsp2header hash -f <path/to/file> -o <path/to/out> */

const char *gRSPPath;

const char *gOutputPath;

RSPKind gCurrentRSPType;

void parse_args(int argc, const char *argv[]) {
    for (int i = 0; i < argc; i++) {
        std::string str = argv[i];
        if (str == "hash") {
            gCurrentRSPType = Hash;
        } else if (str == "-f") {
            gRSPPath = str.c_str();
        } else if (str == "-o") {
            gOutputPath = str.c_str();
        }
    }
}

int main(int argc, const char *argv[]) {

}

