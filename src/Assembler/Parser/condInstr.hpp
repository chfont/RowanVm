#ifndef cond_instr_h
#define cond_instr_h

#include "IntermediateData/emitHex.hpp"
#include "ast.hpp"

namespace parser {
    class CondInstr : public AST {
    public:
        CondInstr(std::string code, std::string cond, std::string regOne, std::string regTwo, std::string label){
            opcode = std::move(code);
            condition = std::move(cond);
            registerOne = std::move(regOne);
            registerTwo = std::move(regTwo);
            jumpLabel = std::move(label);
        }
        std::string emitDebugString() const override{
            return "CONDITIONAL: " + opcode + " "+ condition + " "+ registerOne + " "+ registerTwo + " "+ jumpLabel;
        }

        ASTType getType() const override {
          return ASTType::Conditional;
        }

        std::string emitLabel() const override {
          return jumpLabel;
        }

        std::string emit() const override {
          return EmitHex::EmitHexData::EmitOpcode(opcode) +
                 EmitHex::EmitHexData::EmitCondition(condition) +
                 EmitHex::EmitHexData::EmitRegister(registerOne) +
                 EmitHex::EmitHexData::EmitRegister(registerTwo) +
                 char(0) + char(0) + char(0)+char(0); //Pad 4 bytes for label
        }
    private:
        std::string opcode;
        std::string condition;
        std::string registerOne;
        std::string registerTwo;
        std::string jumpLabel;
    };
}
#endif
