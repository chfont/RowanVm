#ifndef attribute_h
#define attribute_h

#include "ast.hpp"

namespace parser {
  class Attribute : public AST {
    public:
        Attribute(std::string attrName, uint64_t attrVal){
        attributeName = std::move(attrName);
        attributeValue = std::move(attrVal);
      }
      std::string emitDebugString() const override {
        return "ATTRIBUTE: " + attributeName + " : " + std::to_string(attributeValue);
      }
      ASTType getType() const override {
        return ASTType::Attribute;
      }
      std::string emit() const override {
       return "";
      }
      std::string getAttributeName(){ return attributeName;}
      uint64_t getAttributeValue(){return attributeValue;}
    private:
      std::string attributeName;
      uint64_t attributeValue; // kept as string for future cases
  };
}


#endif
