#ifndef single_reg_h
#define single_reg_h

#include "ast.hpp"
#include "IntermediateData/emitHex.hpp"

namespace parser {
    class SingleRegInstr : public AST {
    public:
        SingleRegInstr(std::string code, std::string reg){
            registerName = std::move(reg);
            opcode = std::move(code);
        }
        std::string emitDebugString() const override {
            return "SINGLE_REG: "+ opcode + " " + registerName;
        }
        ASTType getType() const override {
          return ASTType::SingleRegInstr;
        }
        std::string emit() const override {
          return EmitHex::EmitHexData::EmitOpcode(opcode) +
                 EmitHex::EmitHexData::EmitRegister(registerName);
        }
    private:
        std::string registerName;
        std::string opcode;
    };
}

#endif
