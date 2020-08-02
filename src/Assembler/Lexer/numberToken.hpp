#ifndef numbertok_h
#define numbertok_h

#include <iostream>
#include <string>
#include <utility>

#include "token.hpp"

namespace token {
class NumberToken : public Token {
public:
  NumberToken(std::string s) { value = s;}
  std::string emitDebugString() const override { return "INT: " + value; }
  std::string emit() const override {return value;}
  TokenType getType() const override {return TokenType::NUM;}
private:
  std::string value;
};
}

#endif
