
#ifndef optok_h
#define optok_h

#include <iostream>
#include <utility>

#include "token.hpp"
namespace token {

class OpcodeToken : public Token {
public:
  OpcodeToken(std::string code) { opcode = code;}
  std::string emitDebugString() const override { return "OPCODE: " + opcode; }
  std::string emit() const override {return opcode; }
  TokenType getType() const override {return TokenType::OPCODE;}
private:
  std::string opcode;
};

}

#endif
