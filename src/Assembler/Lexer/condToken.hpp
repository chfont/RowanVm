#ifndef condtok_h
#define condtok_h

#include <iostream>

#include "../../IntermediateData/condition.hpp"
#include "token.hpp"
namespace token {
class CondToken : public Token {
public:
  CondToken(condition::Condition cond) { condition = cond;}

  std::string emitDebugString() const override {
    return std::string("CONDITION: ") + condition::condMap.at(condition);
  }
  std::string emit() const override {
      return condition::condMap.at(condition);
  }
  TokenType getType() const override {return TokenType::COND;}
private:
  condition::Condition condition;
};
}

#endif
