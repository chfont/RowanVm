#ifndef opcodetype_h
#define opcodetype_h

#include <string>
#include <map>

namespace parser {
    enum class OpcodeType {
        TWO_REG,
        REG_NUM,
        NOP,
        CONDITIONAL,
        ONE_REG
    };

    static std::map<std::string, OpcodeType> OpcodeMap {
            {"nop", OpcodeType::NOP},
            {"cjump",OpcodeType::CONDITIONAL},
            {"pr", OpcodeType::ONE_REG},
            {"prb", OpcodeType::ONE_REG},
            {"ld", OpcodeType::TWO_REG},
            {"add", OpcodeType::TWO_REG},
            {"sub", OpcodeType::TWO_REG},
            {"mult", OpcodeType::TWO_REG},
            {"div", OpcodeType::TWO_REG},
            {"st", OpcodeType::REG_NUM},
            {"ldc", OpcodeType::REG_NUM},
            {"addc", OpcodeType::REG_NUM},
            {"subc", OpcodeType::REG_NUM},
            {"multc", OpcodeType::REG_NUM},
            {"divc", OpcodeType::REG_NUM}
    };
}
#endif
