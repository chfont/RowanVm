#include "lexer.hpp"

#include <algorithm>
#include <memory>
#include <vector>

#include "IntermediateData/condition.hpp"
#include "IntermediateData/opcodeData.hpp"
#include "colonToken.hpp"
#include "condToken.hpp"
#include "labelToken.hpp"
#include "numberToken.hpp"
#include "opcodeToken.hpp"
#include "registerToken.hpp"
#include "braceToken.hpp"

namespace lexer {
Lexer::Lexer(std::string input) {
  program = std::move(input);
  index = 0;
  lineNumber = 0;
  buffer = "";
}

bool isbrace(char c){
  return c == '{' || c == '}';
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
    return std::make_unique<token::ColonToken>();
  } else if (*nextChar == '{') {
    return std::make_unique<token::LBraceToken>();
  } else if (*nextChar == '}') {
    return std::make_unique<token::RBraceToken>();
  } else if (isdigit(*nextChar) || *nextChar == '-') {
    buffer += *nextChar;
    nextChar = getNextChar();
    while (nextChar != nullptr && !isspace(*nextChar) && isdigit(*nextChar)) {
      buffer += *nextChar;
      nextChar = getNextChar();
    }
    if (nextChar != nullptr && !isdigit(*nextChar) && !isspace(*nextChar) &&
        !isbrace(*nextChar)) {
      std::cout << "Unrecognizable construct at line " << index << std::endl;
      return nullptr;
    } else {
      return std::make_unique<token::NumberToken>(buffer);
    }
  } else if (isalpha(*nextChar)) {
    buffer += *nextChar;
    nextChar = getNextChar();
    while (nextChar != nullptr && !isspace(*nextChar) &&
           (isalpha(*nextChar) || *nextChar == '_')) {
      buffer += *nextChar;
      nextChar = getNextChar();
    }
    if (nextChar != nullptr && *nextChar == ':') {
      index--;
    }
    std::transform(buffer.begin(), buffer.end(), buffer.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    if (std::find(registers.begin(), registers.end(), buffer) !=
        registers.end()) {
      return std::make_unique<token::RegisterToken>(buffer);
    }
    if (opcodeData::Opcodes.count(buffer)) {
      return std::make_unique<token::OpcodeToken>(buffer);
    }
    if (condition::stringCondMap.count(buffer) > 0) {
      return std::make_unique<token::CondToken>(
          condition::stringCondMap.at(buffer));
    }
    return std::make_unique<token::LabelToken>(buffer);
  } else {
    return nullptr; //should error handle?
  }
}

char *Lexer::getNextChar() {
  if (index >= program.length()) {
    return nullptr;
  }
  return &(program[index++]);
}
} // namespace lexer
