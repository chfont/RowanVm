#ifndef nop_h
#define nop_h

#include "../../IntermediateData/emitHex.hpp"
#include "ast.hpp"
#include <string>

namespace parser {
    class Nop : public AST {
    public:
        std::string emitDebugString() const override {return "NOP";}
        ASTType getType() const override {
          return ASTType::Nop;
        }
        std::string emit() const override{
          return std::string(1,EmitHex::EmitHexData::EmitOpcode("nop"));
        }
    };
}
#endif