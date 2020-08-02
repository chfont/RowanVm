#ifndef lextest_h
#define lextest_h

#include "../src/IntermediateData/condition.hpp"
#include "colonToken.hpp"
#include "condToken.hpp"
#include "labelToken.hpp"
#include "lexer.hpp"
#include "numberToken.hpp"
#include "opcodeToken.hpp"
#include "registerToken.hpp"
#include "token.hpp"
#include "gtest/gtest.h"
#include <array>

using token_ptr = std::unique_ptr<token::Token>;

TEST(Lexer_Test, ParseDiffRasm){
    auto content = "ldc ra 5\n"
                   "ldc rb 10\n"
                   "ldc rc 1\n"
                   "ldc rd 0\n"
                   "LOOP:\n"
                   "cjump le rb ra END\n"
                   "add rd rc \n"
                   "sub rb rc\n"
                   "cjump eq rd rd LOOP ; Don't have an unconditional jump yet\n"
                   "\n"
                   "END:\n"
                   "pr rd";
    auto lex = lexer::Lexer(content);
    auto tokens = std::array<token_ptr,34> {
            token_ptr(new token::OpcodeToken("ldc")),
            token_ptr(new token::RegisterToken("ra")),
            token_ptr(new token::NumberToken("5")),
            token_ptr(new token::OpcodeToken("ldc")),
            token_ptr(new token::RegisterToken("rb")),
            token_ptr(new token::NumberToken("10")),
            token_ptr(new token::OpcodeToken("ldc")),
            token_ptr(new token::RegisterToken("rc")),
            token_ptr(new token::NumberToken("1")),
            token_ptr(new token::OpcodeToken("ldc")),
            token_ptr(new token::RegisterToken("rd")),
            token_ptr(new token::NumberToken("0")),
            token_ptr(new token::LabelToken("loop")),
            token_ptr(new token::ColonToken()),
            token_ptr(new token::OpcodeToken("cjump")),
            token_ptr(new token::CondToken(condition::Condition::LE)),
            token_ptr(new token::RegisterToken("rb")),
            token_ptr(new token::RegisterToken("ra")),
            token_ptr(new token::LabelToken("end")),
            token_ptr(new token::OpcodeToken("add")),
            token_ptr(new token::RegisterToken("rd")),
            token_ptr(new token::RegisterToken("rc")),
            token_ptr(new token::OpcodeToken("sub")),
            token_ptr(new token::RegisterToken("rb")),
            token_ptr(new token::RegisterToken("rc")),
            token_ptr(new token::OpcodeToken("cjump")),
            token_ptr(new token::CondToken(condition::Condition::EQ)),
            token_ptr(new token::RegisterToken("rd")),
            token_ptr(new token::RegisterToken("rd")),
            token_ptr(new token::LabelToken("loop")),
            token_ptr(new token::LabelToken("end")),
            token_ptr(new token::ColonToken()),
            token_ptr(new token::OpcodeToken("pr")),
            token_ptr(new token::RegisterToken("rd")),
    };
    for(int i = 0; i < tokens.size(); i++){
        ASSERT_EQ(*(tokens[i]), *(lex.getNextToken()));
    }

    ASSERT_EQ(nullptr, lex.getNextToken());
}

TEST(Lexer_Test, LexNop){
  auto code = "nop\n";
  auto lex = lexer::Lexer(code);
  ASSERT_EQ(*token_ptr(new token::OpcodeToken("nop")), *(lex.getNextToken()));
  ASSERT_EQ(nullptr, lex.getNextToken());
}

TEST(Lexer_Test, LexStatement){
  auto code = "ldc ra 500";
  auto lex = lexer::Lexer(code);
  auto expectedTokens = std::array<token_ptr,3>{
      token_ptr(new token::OpcodeToken("ldc")),
      token_ptr(new token::RegisterToken("ra")),
      token_ptr(new token::NumberToken("500"))
  };
  for(int i =0; i < expectedTokens.size(); i++){
    ASSERT_EQ(*(expectedTokens[i]), *(lex.getNextToken()));
  }
  ASSERT_EQ(nullptr, lex.getNextToken());
}

#endif
