#ifndef labeltok_h
#define labeltok_h

#include <iostream>
#include <string>
#include <utility>

#include "token.hpp"
namespace token {
class LabelToken : public Token {
public:
  LabelToken(std::string s) { label = std::move(s); }

  std::string emit() const { return "LABEL: " + label; }

private:
  std::string label;
};
} // namespace token
#endif
