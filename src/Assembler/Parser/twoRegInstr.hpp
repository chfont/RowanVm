#ifndef reginstr_h
#define reginstr_h

#include "../../IntermediateData/emitHex.hpp"
#include "ast.hpp"

namespace parser {
    class twoRegInstr : public AST {
    public:
      twoRegInstr(std::string instr, std::string registerOne, std::string registerTwo){
            opcode = std::move(instr);
            regOne = std::move(registerOne);
            regTwo = std::move(registerTwo);
        }
        std::string emitDebugString() const override {
            return "TWO_REG: "+opcode+" " + regOne + " " + regTwo;
        }
        ASTType getType() const override {
          return ASTType::TwoRegInstr;
        }
        std::string emit() const override {
          return EmitHex::EmitHexData::EmitOpcode(opcode) +
                 EmitHex::EmitHexData::EmitRegister(regOne) +
                 EmitHex::EmitHexData::EmitRegister(regTwo);
        }
    private:
        std::string regOne;
        std::string regTwo;
        std::string opcode;
    };
}

#endif
