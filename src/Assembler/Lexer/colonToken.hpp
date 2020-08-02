#ifndef semicolon_h
#define semicolon_h

#include <iostream>

#include "token.hpp"

namespace token {
class ColonToken : public Token {
public:
    std::string emitDebugString() const override { return "COLON"; }
    std::string emit() const override {return emitDebugString();}
    TokenType getType() const override {return TokenType::COLON;}
};
}
#endif
