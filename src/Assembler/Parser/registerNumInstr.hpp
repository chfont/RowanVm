#ifndef regnum_h
#define regnum_h

#include "ast.hpp"
#include "IntermediateData/emitHex.hpp"

namespace parser {
    class RegisterNumInstr : public AST {
    public:
        RegisterNumInstr(std::string code, std::string reg, std::string num){
            opcode = std::move(code);
            registerName = std::move(reg);
            number = std::move(num);
        }

        std::string emitDebugString() const override {
            return "REG_NUM: "+opcode + " " + registerName + " " + number;
        }
        ASTType getType() const override {
          return ASTType::RegNum;
        }

        std::string emit() const override {
          auto hexData = EmitHex::EmitHexData::EmitOpcode(opcode) +
                 EmitHex::EmitHexData::EmitRegister(registerName) +
                 EmitHex::EmitHexData::EmitInteger(number);
          while (hexData.size() < 6){
            hexData += char(0);
          }
          return hexData;
        }

        size_t size() const override {
            return 6;
        }

    private:
        std::string opcode;
        std::string registerName;
        std::string number;
    };
}
#endif
