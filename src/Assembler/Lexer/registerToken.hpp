
#ifndef regtok_h
#define regtok_h

#include <iostream>
#include <string>
#include <utility>

#include "token.hpp"

namespace token {
class RegisterToken : public Token {
public:
  RegisterToken(std::string regName) { registerName = regName; }

  std::string emitDebugString() const override { return "REGISTER: " + registerName; }
  std::string emit() const override {return registerName;}
  TokenType getType() const override {return TokenType::REG;}
private:
  std::string registerName;
};
}
#endif
