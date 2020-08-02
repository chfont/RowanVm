#ifndef labeltok_h
#define labeltok_h

#include <iostream>
#include <string>
#include <utility>

#include "token.hpp"
namespace token {
class LabelToken : public Token {
public:
  LabelToken(std::string s) { label = s;}

  std::string emitDebugString() const override { return "LABEL: " + label; }
  std::string emit() const override {return label;}
  TokenType getType() const override {return TokenType::LABEL;}
private:
  std::string label;
};
}
#endif
