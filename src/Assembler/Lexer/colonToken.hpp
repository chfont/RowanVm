#ifndef semicolon_h
#define semicolon_h

#include <iostream>

#include "token.hpp"

namespace token {
class ColonToken : public Token {
public:
  std::string emit() const { return "COLON"; }
};
} // namespace token
#endif
