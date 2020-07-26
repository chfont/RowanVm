
#ifndef optok_h
#define optok_h

#include <iostream>
#include <utility>

#include "../opcode.hpp"
#include "token.hpp"
namespace token {

class OpcodeToken : public Token {
public:
  OpcodeToken(std::string code) { opcode = std::move(code); }
  std::string emit() const { return "OPCODE: " + opcode; }

private:
  std::string opcode;
};

} // namespace token

#endif
