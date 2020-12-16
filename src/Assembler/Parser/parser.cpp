#include "parser.hpp"
#include "condInstr.hpp"
#include "labelAst.hpp"
#include "labelInstr.hpp"
#include "nop.hpp"
#include "registerNumInstr.hpp"
#include "singleRegInstr.hpp"
#include "twoRegInstr.hpp"
#include "IntermediateData/opcodeData.hpp"
#include "attribute.hpp"
#include <iostream>
#include <utility>

namespace parser {
    Parser::Parser(std::string input) : lexer(std::move(input)){
    }

    std::vector<std::unique_ptr<AST>> Parser::parse() {
        auto nodes = std::vector<std::unique_ptr<AST>>();
        auto nextToken = lexer.getNextToken();
        while(nextToken != nullptr){
            switch (nextToken->getType()){
                case token::TokenType::LABEL :{
                    auto node = parseLabel(std::move(nextToken));
                    if(node == nullptr){
                        return nodes;
                    }
                    nodes.push_back(std::move(node));
                    break;
                }
                case token::TokenType::OPCODE:{
                    auto node = parseOpcode((std::move(nextToken)));
                    if(node == nullptr){
                        return nodes;
                    }
                    nodes.push_back(std::move(node));
                    break;
                }
                case token::TokenType::LBRACE:{
                    auto node = parseAttribute();
                    if (node == nullptr){
                      return nodes;
                    }
                    nodes.push_back(std::move(node));
                    break;
                }
                default: {
                   std::cout << "Token (" << nextToken->emitDebugString() << ") cannot start a statement" << std::endl;
                   //Maybe return null here instead?
                   return nodes;
                }
            }
            nextToken = lexer.getNextToken();
        }
        return nodes;
    }

    std::unique_ptr<AST> Parser::parseLabel(std::unique_ptr<token::Token> token){
        if(token->getType() != token::TokenType::LABEL) {
            throw std::logic_error("Invalid call to parse label");
        }
        auto nextToken = lexer.getNextToken();
        if(nextToken == nullptr){
            std::cerr << "Unexpected end of input, expected colon (:)" << std::endl;
            return nullptr;
        }
        if(nextToken->getType() != token::TokenType::COLON){
            std::cerr << "Expected colon (:), found " << nextToken->emitDebugString() << std::endl;
            return nullptr;
        }

        return std::unique_ptr<AST>(new Label(token->emit()));
    }

    std::unique_ptr<AST> Parser::parseOpcode(std::unique_ptr<token::Token> opcodeTok){
        if(opcodeTok->getType() != token::TokenType::OPCODE) {
            throw std::logic_error("Invalid call to parse opcode");
        }
        auto instruction = opcodeTok->emit();
        auto opType = opcodeData::Opcodes.at(instruction).type;
        switch (opType){
            case opcodeData::OpcodeType::NOP:
                return std::unique_ptr<AST>(new Nop());
            case opcodeData::OpcodeType::ONE_REG: {
                auto nextTok = lexer.getNextToken();
                if(! assertTokenType(nextTok,token::TokenType::REG)){
                    return nullptr;
                }
                auto regNameOne = nextTok->emit();
                return std::unique_ptr<AST>( new SingleRegInstr(instruction,regNameOne));
            }
            case opcodeData::OpcodeType::TWO_REG: {
                auto nextTok = lexer.getNextToken();
                if(! assertTokenType(nextTok,token::TokenType::REG)){
                    return nullptr;
                }
                auto regNameOne = nextTok->emit();

                nextTok = lexer.getNextToken();
                if(! assertTokenType(nextTok,token::TokenType::REG)){
                    return nullptr;
                }
                auto regNameTwo = nextTok->emit();
                return std::unique_ptr<AST>(new twoRegInstr(instruction,regNameOne, regNameTwo));
            }

            case opcodeData::OpcodeType::REG_NUM: {
                auto nextTok = lexer.getNextToken();
                if(! assertTokenType(nextTok,token::TokenType::REG)){
                    return nullptr;
                }
                auto regNameOne = nextTok->emit();

                nextTok = lexer.getNextToken();
                if(! assertTokenType(nextTok,token::TokenType::NUM)){
                    return nullptr;
                }

                auto num = nextTok->emit();
                return std::unique_ptr<AST>(new RegisterNumInstr(instruction, regNameOne, num));
            }

            case opcodeData::OpcodeType::CONDITIONAL: {
                auto nextTok = lexer.getNextToken();
                if(! assertTokenType(nextTok, token::TokenType::COND)){
                    return nullptr;
                }
                auto condition = nextTok->emit();

                nextTok = lexer.getNextToken();
                if(! assertTokenType(nextTok,token::TokenType::REG)){
                    return nullptr;
                }
                auto regNameOne = nextTok->emit();

                nextTok = lexer.getNextToken();
                if(! assertTokenType(nextTok,token::TokenType::REG)){
                    return nullptr;
                }
                auto regNameTwo = nextTok->emit();

                nextTok = lexer.getNextToken();
                if(! assertTokenType(nextTok, token::TokenType::LABEL)){
                    return nullptr;
                }
                auto label = nextTok->emit();
                return std::unique_ptr<AST>(new CondInstr(instruction, condition, regNameOne, regNameTwo, label));
            }
            case opcodeData::OpcodeType::JUMP: {
              auto nextTok = lexer.getNextToken();
              if(! assertTokenType(nextTok, token::TokenType::LABEL)){
                return nullptr;
              }
              return std::unique_ptr<AST>(new LabelInstr(instruction, nextTok->emit()));
            }
            default:
              return nullptr;
        }
    }

    std::unique_ptr<AST> Parser::parseAttribute(){
      //take in attribute
      auto attrToken = lexer.getNextToken();
      if(!assertTokenType(attrToken, token::TokenType::LABEL)){
        std::cerr << "Unexpected construct, expected string" << std::endl;
        return nullptr;
      }
      //take in value
      auto valueToken = lexer.getNextToken();
      if(!assertTokenType(valueToken, token::TokenType::NUM)){
        std::cerr << "Unexpected construct, expected number" << std::endl;
        return nullptr;
      }
      // get RBRACE
      auto braceToken = lexer.getNextToken();
      if(!assertTokenType(braceToken, token::TokenType::RBRACE)){
        std::cerr << "Expected '{', got " + braceToken->emitDebugString() << std::endl;
        return nullptr;
      }
      if(valueToken->emit()[0] == '-'){
        std::cerr << "Invalid value for attribute, must be > 0" << std::endl;
        return nullptr;
      }
      return std::make_unique<parser::Attribute>(attrToken->emit(), std::stoull(valueToken->emit()));
    }

    bool Parser::assertTokenType(std::unique_ptr<token::Token> const& token, token::TokenType type){
        if(token == nullptr){
            std::cerr << "Unexpected end of file, was expecting" << types[int(type)] << std::endl;
            return false;
        } else if(token->getType() != type){
            std::cerr << "Unexpected token received, found " << types[int(token->getType())] <<", was expecting " << types[int(type)] << std::endl;
            return false;
        }
        return true;
    }
}
