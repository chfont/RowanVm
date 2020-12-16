#ifndef parser_h
#define parser_h

#include "Lexer/lexer.hpp"
#include "Lexer/token.hpp"
#include "ast.hpp"
#include <algorithm>
#include <memory>
#include <vector>
#include <array>

namespace parser {
    class Parser {
    public:
        explicit Parser(std::string input);
        std::vector<std::unique_ptr<AST>> parse();
    private:
        lexer::Lexer lexer;

        std::unique_ptr<AST> parseLabel(std::unique_ptr<token::Token> label);
        std::unique_ptr<AST> parseOpcode(std::unique_ptr<token::Token> opcode);
        std::unique_ptr<AST> parseAttribute();
        bool assertTokenType(std::unique_ptr<token::Token> const& token, token::TokenType type);
        const std::array<std::string, 6> types {
                "number",
                "label",
                "opcode",
                "register",
                "condition",
                "colon (:)"
        };
    };
}
#endif
