#ifndef lbrace_token_h
#define lbrace_token_h

#include "token.hpp"
namespace token {
  class LBraceToken : public token::Token {
     public:
       LBraceToken(){}
       std::string emitDebugString() const override { return "LBRACE";}
       std::string emit() const override {return "";}
       TokenType getType() const override {return TokenType::LBRACE;}
  };

  class RBraceToken : public token::Token {
    public:
      RBraceToken(){}
      std::string emitDebugString() const override { return "RBRACE";}
      std::string emit() const override {return "";}
      TokenType getType() const override {return TokenType::RBRACE;}
};
}
#endif
