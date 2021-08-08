#ifndef labelNode_h
#define labelNode_h

#include "ast.hpp"

namespace parser {

    class Label : public AST {
    public:
        Label(std::string label){
            name = std::move(label);
        }
        std::string emitDebugString() const override {
            return "LABEL: " + name;
        }
        std::string emitLabel() const override {
          return name;
        }

        ASTType getType() const override {
          return ASTType::Label;
        }
        std::string emit() const override {
          return "";
        }

        size_t size() const override {
            return 0;
        }
    private:
        std::string name;
    };
}

#endif
