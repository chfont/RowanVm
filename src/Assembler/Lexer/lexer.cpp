#include "lexer.hpp"

#include <algorithm>
#include <vector>

#include "IntermediateData/condition.hpp"
#include "IntermediateData/opcodeData.hpp"
#include "colonToken.hpp"
#include "condToken.hpp"
#include "labelToken.hpp"
#include "numberToken.hpp"
#include "opcodeToken.hpp"
#include "registerToken.hpp"

namespace lexer {
Lexer::Lexer(std::string input) {
  program = std::move(input);
  index = 0;
  lineNumber = 0;
  buffer = "";
}

std::unique_ptr<token::Token> Lexer::getNextToken() {
  buffer.clear();
  auto nextChar = getNextChar();
  while (nextChar == nullptr || isspace(*nextChar) || *nextChar == ';') {
    if (nextChar == nullptr) {
      return nullptr;
    }
    if (*nextChar == ';') {
      while (*nextChar != '\n') {
        nextChar = getNextChar();
        if (nextChar == nullptr) {
          return nullptr;
        }
      }
    }
    if (*nextChar == '\n') {
      lineNumber++;
    }
    nextChar = getNextChar();
  }
  if (*nextChar == ':') {
    return std::unique_ptr<token::Token>(new token::ColonToken());
  }
  if (isdigit(*nextChar) || *nextChar == '-') {
    buffer += *nextChar;
    nextChar = getNextChar();
    while (nextChar != nullptr && !isspace(*nextChar) && isdigit(*nextChar)) {
      buffer += *nextChar;
      nextChar = getNextChar();
    }
    if (nextChar != nullptr && !isdigit(*nextChar) && !isspace(*nextChar)) {
      std::cout << "Unrecognizable construct at line " << index << std::endl;
      return nullptr;
    } else {
      return std::unique_ptr<token::Token>(new token::NumberToken(buffer));
    }
  }
  if (isalpha(*nextChar)) {
    buffer += *nextChar;
    nextChar = getNextChar();
    while (nextChar != nullptr && !isspace(*nextChar) && isalpha(*nextChar)) {
      buffer += *nextChar;
      nextChar = getNextChar();
    }
    if (nextChar != nullptr && !isalpha(*nextChar) && !isspace(*nextChar) &&
        *nextChar != ':') {
      std::cout << "Unrecognizable construct at line " << index << std::endl;
      return nullptr;
    } else {
      if (nextChar != nullptr && *nextChar == ':') {
        index--;
      }
      std::transform(buffer.begin(), buffer.end(), buffer.begin(),
                     [](unsigned char c) { return std::tolower(c); });
      if (std::find(registers.begin(), registers.end(), buffer) !=
          registers.end()) {
        return std::unique_ptr<token::Token>(new token::RegisterToken(buffer));
      }
      if (opcodeData::Opcodes.count(buffer)) {
        return std::unique_ptr<token::Token>(new token::OpcodeToken(buffer));
      }
      if (condition::stringCondMap.count(buffer) > 0) {
        return std::unique_ptr<token::Token>(
            new token::CondToken(condition::stringCondMap.at(buffer)));
      }
      return std::unique_ptr<token::Token>(new token::LabelToken(buffer));
    }
  }
}

char *Lexer::getNextChar() {
  if (index >= program.length()) {
    return nullptr;
  }
  return &(program[index++]);
}
} // namespace lexer
