#ifndef lextest_h
#define lextest_h

#include "lexer.hpp"
#include "gtest/gtest.h"
#include "token.hpp"
#include "opcodeToken.hpp"
#include "registerToken.hpp"
#include "condToken.hpp"
#include "labelToken.hpp"
#include "numberToken.hpp"
#include "colonToken.hpp"
#include "../src/condition.hpp"
#include <array>

TEST(Lexer_Test, ParseDiffRasm){
    auto content = "ld ra 5\n"
                   "ld rb 10\n"
                   "ld rc 1\n"
                   "ld rd 0\n"
                   "LOOP:\n"
                   "cjump le rb ra END\n"
                   "add rd rc \n"
                   "sub rb rc\n"
                   "cjump eq rd rd LOOP ; Don't have an unconditional jump yet\n"
                   "\n"
                   "END:\n"
                   "pr rd";
    auto token = std::unique_ptr<token::Token>(new token::OpcodeToken("ld"));
    auto lex = lexer::Lexer(content);
    auto tokens = std::array<std::unique_ptr<token::Token>,34> {
            std::unique_ptr<token::Token>(new token::OpcodeToken("ld")),
            std::unique_ptr<token::Token>(new token::RegisterToken("ra")),
            std::unique_ptr<token::Token>(new token::NumberToken("5")),
            std::unique_ptr<token::Token>(new token::OpcodeToken("ld")),
            std::unique_ptr<token::Token>(new token::RegisterToken("rb")),
            std::unique_ptr<token::Token>(new token::NumberToken("10")),
            std::unique_ptr<token::Token>(new token::OpcodeToken("ld")),
            std::unique_ptr<token::Token>(new token::RegisterToken("rc")),
            std::unique_ptr<token::Token>(new token::NumberToken("1")),
            std::unique_ptr<token::Token>(new token::OpcodeToken("ld")),
            std::unique_ptr<token::Token>(new token::RegisterToken("rd")),
            std::unique_ptr<token::Token>(new token::NumberToken("0")),
            std::unique_ptr<token::Token>(new token::LabelToken("loop")),
            std::unique_ptr<token::Token>(new token::ColonToken()),
            std::unique_ptr<token::Token>(new token::OpcodeToken("cjump")),
            std::unique_ptr<token::Token>(new token::CondToken(Condition::LE)),
            std::unique_ptr<token::Token>(new token::RegisterToken("rb")),
            std::unique_ptr<token::Token>(new token::RegisterToken("ra")),
            std::unique_ptr<token::Token>(new token::LabelToken("end")),
            std::unique_ptr<token::Token>(new token::OpcodeToken("add")),
            std::unique_ptr<token::Token>(new token::RegisterToken("rd")),
            std::unique_ptr<token::Token>(new token::RegisterToken("rc")),
            std::unique_ptr<token::Token>(new token::OpcodeToken("sub")),
            std::unique_ptr<token::Token>(new token::RegisterToken("rb")),
            std::unique_ptr<token::Token>(new token::RegisterToken("rc")),
            std::unique_ptr<token::Token>(new token::OpcodeToken("cjump")),
            std::unique_ptr<token::Token>(new token::CondToken(Condition::EQ)),
            std::unique_ptr<token::Token>(new token::RegisterToken("rd")),
            std::unique_ptr<token::Token>(new token::RegisterToken("rd")),
            std::unique_ptr<token::Token>(new token::LabelToken("loop")),
            std::unique_ptr<token::Token>(new token::LabelToken("end")),
            std::unique_ptr<token::Token>(new token::ColonToken()),
            std::unique_ptr<token::Token>(new token::OpcodeToken("pr")),
            std::unique_ptr<token::Token>(new token::RegisterToken("rd")),
    };
    for(int i = 0; i < tokens.size(); i++){
        ASSERT_EQ(*(tokens[i]), *(lex.getNextToken()));
    }

    ASSERT_EQ(nullptr, lex.getNextToken());
}

#endif
