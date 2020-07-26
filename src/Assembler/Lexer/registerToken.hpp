
#ifndef regtok_h
#define regtok_h

#include <iostream>
#include <string>
#include <utility>

#include "token.hpp"

namespace token {
class RegisterToken : public Token {
public:
  RegisterToken(std::string regName) { registerName = std::move(regName); }

  std::string emit() const { return "REGISTER: " + registerName; }

private:
  std::string registerName;
};
} // namespace token
#endif
