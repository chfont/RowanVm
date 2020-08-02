#ifndef ast_h
#define ast_h

#include <string>
#include <stdexcept>
namespace parser {
    enum class ASTType {
      Nop,
      SingleRegInstr,
      TwoRegInstr,
      Conditional,
      RegNum,
      Label
    };

    class AST {
    public:
        virtual std::string emitDebugString() const = 0;
        virtual std::string emitLabel() const {
          throw std::logic_error("Cannot emit label on non-label node");
        }
        virtual ASTType getType() const = 0;
        virtual std::string emit() const = 0;
    };

    inline bool operator== (const AST &lhs, const AST &rhs){
      return lhs.getType() == rhs.getType() &&
             lhs.emitDebugString() == rhs.emitDebugString();
    }
}

#endif
