#ifndef label_instr_h
#define label_instr_h

#include "ast.hpp"
#include <IntermediateData/emitHex.hpp>
namespace parser {
    class LabelInstr : public AST {

    public:
      LabelInstr(std::string instr, std::string label){
        opcode = std::move(instr);
        this->label = std::move(label);
      }
      ASTType getType() const override {
        return ASTType::LabelInstr;
      }
      std::string emit() const override{
        return std::string(1,EmitHex::EmitHexData::EmitOpcode(opcode))
               + char(0)+char(0)+char(0)+char(0); // pad with 4 empty bytes;
      }
      std::string emitDebugString() const override {
        return "LABEL_INSTR: "+opcode + " " + label;
      }
      std::string emitLabel() const override {
        return label;
      }
    private:
      std::string opcode;
      std::string label;
    };
}
#endif
