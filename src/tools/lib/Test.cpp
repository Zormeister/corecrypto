//
//  Test.cpp
//  corecrypto
//
//  Created by Zormeister on 3/6/2025.
//

#include "RSPParser.hpp"
#include <vector>

using namespace CoreCrypto::RSP;

enum struct KeyType {
    Input,
    Output,
    Key,
    IV,
    Tag,
    AAD,
    MsgLength
};

/*
 * 'enter' key is encoded as 0D 0A according to Okteta.
 */

struct KeyMapping {
    const std::string_view Key;
    KeyType Type;
    Test::Operation Operation;
};

KeyMapping gParsingMap[] = {
    {"Len", KeyType::MsgLength, Test::Operation::Hash},
    {"Msg", KeyType::Input, Test::Operation::Hash},
    {"MD", KeyType::Output, Test::Operation::Hash},
    {"Key", KeyType::Key, Test::Operation::Decrypt},
    {"KEY", KeyType::Key, Test::Operation::Decrypt},
    {"IV", KeyType::IV, Test::Operation::Decrypt},
    {"Key", KeyType::Key, Test::Operation::Encrypt},
    {"KEY", KeyType::Key, Test::Operation::Encrypt},
    {"IV", KeyType::IV, Test::Operation::Encrypt},
    {"PLAINTEXT", KeyType::Input, Test::Operation::Encrypt},
    {"CIPHERTEXT", KeyType::Output, Test::Operation::Encrypt},
    {"PLAINTEXT", KeyType::Output, Test::Operation::Decrypt},
    {"CIPHERTEXT", KeyType::Input, Test::Operation::Decrypt},

};

Test::Test(std::vector<char> rsp, Test::Operation op) {
    this->_operation = op;

    
}
