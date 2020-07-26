#ifndef numbertok_h
#define numbertok_h

#include <iostream>
#include <string>
#include <utility>

#include "token.hpp"

namespace token {
class NumberToken : public Token {
public:
  NumberToken(std::string s) { value = std::move(s); }
  std::string emit() const { return "INT: " + value; }

private:
  std::string value;
};
} // namespace token

#endif
