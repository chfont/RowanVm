#ifndef condtok_h
#define condtok_h

#include <iostream>

#include "../../condition.hpp"
#include "token.hpp"
namespace token {
class CondToken : public Token {
public:
  CondToken(Condition::Condition cond) { condition = cond; }

  std::string emit() const {
    return std::string("CONDITION: ") + Condition::condMap.at(condition);
  }

private:
  Condition::Condition condition;
};
} // namespace token

#endif
