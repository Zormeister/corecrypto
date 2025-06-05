//
//  RSPParser.hpp
//  corecrypto
//
//  Created by Zormeister on 3/6/2025.
//

#include <optional>
#include <string>
#include <vector>
#include <cstdint>

/* Make this clean in case this gets reused anywhere. */
namespace CoreCrypto {

    namespace RSP {

        class Test {
            public:
            enum struct Operation {
                Hash,
                Encrypt,
                Decrypt,
            };

            public:
            Test(std::vector<char> rspData, Operation op); /* op should be fed by the parser. */

            const std::vector<uint8_t> &getInputData() { return _input; };
            const std::vector<uint8_t> &getExpectedResult() { return _expected; };
            const std::vector<uint8_t> &getInitializationVector() { return _iv; };
            const std::vector<uint8_t> &getMAC() { return _mac; };
            const std::vector<uint8_t> &getTag() { return _tag; };

            const size_t getLength();

            const Operation getOperation();

            const bool isHashTest() { return _operation == Operation::Hash; };
            const bool hasIV() { return _hasIV; };
            const bool hasKey() { return _hasKey; };
            const bool hasAAD() { return _hasAAD; };
            const bool hasTag() { return _hasTag; };

            private:
            Operation _operation;

            bool _hasIV {false};
            bool _hasAAD {false};
            bool _hasKey {false};
            bool _hasTag {false};

            std::vector<uint8_t> _input;
            std::vector<uint8_t> _expected;
            std::vector<uint8_t> _iv;
            std::vector<uint8_t> _add;
            std::vector<uint8_t> _tag;
            std::vector<uint8_t> _mac;
        };

        class Parser {
            public:
            Parser(std::vector<char> rsp);

            std::vector<Test> GetTestVectors();
        };

    }

};
