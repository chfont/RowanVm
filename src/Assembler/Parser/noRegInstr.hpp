#ifndef noreg_h
#define noreg_h

#include "ast.hpp"
#include "IntermediateData/emitHex.hpp"
namespace parser {
  class NoRegInstr : public AST {
  private:
      std::string opcode;
    public:
      NoRegInstr(std::string op){ opcode = std::move(op);}
      virtual std::string emitDebugString() const override {
        return opcode;
      }
      virtual ASTType getType() const override {return ASTType::Nop;}
      virtual std::string emit() const override {
        return std::string(1,EmitHex::EmitHexData::EmitOpcode(opcode));}

      size_t size() const override {
          return 1;
      }
  };
}
#endif
