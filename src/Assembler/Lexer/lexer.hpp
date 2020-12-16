
#ifndef lex_h
#define lex_h

#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "token.hpp"

namespace lexer {

class Lexer {
public:
  Lexer(std::string input);
  std::unique_ptr<token::Token> getNextToken();

private:
  std::string program;
  std::string buffer;
  unsigned long long index;
  unsigned long long lineNumber;
  char *getNextChar();
};

const auto registers =
    std::vector<std::string>{"ra", "rb", "rc", "rd", "re", "rf", "rg", "rh",
                             "ri", "rj", "rk", "rl", "rm", "rn", "ro", "rp"};
}
#endif
