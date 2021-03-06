#ifndef parser_test_h
#define parser_test_h

#include <Parser/labelInstr.hpp>
#include <Parser/labelAst.hpp>
#include "Parser/parser.hpp"
#include "gtest/gtest.h"
#include "Parser/nop.hpp"
#include "Parser/registerNumInstr.hpp"
#include "Parser/attribute.hpp"


TEST(ParserTests, ParseNop){
  const auto code = "nop";
  const auto nopNode = std::unique_ptr<parser::AST>(new parser::Nop());
  auto parser = parser::Parser(code);
  auto nodes = parser.parse();
  ASSERT_EQ(nodes.size(), 1);
  ASSERT_EQ(*(nodes[0]), *nopNode);
}

TEST(ParserTests, ParseConstArith){
  const auto code = "addc ra 52\n"
                    "subc ra 52\n"
                    "divc ra 5\n"
                    "multc ra 2\n";
  auto expectedNodes = std::array<std::unique_ptr<parser::AST>,4>{
      std::unique_ptr<parser::AST>(new parser::RegisterNumInstr("addc","ra","52")),
      std::unique_ptr<parser::AST>(new parser::RegisterNumInstr("subc","ra","52")),
      std::unique_ptr<parser::AST>(new parser::RegisterNumInstr("divc","ra","5")),
      std::unique_ptr<parser::AST>(new parser::RegisterNumInstr("multc","ra","2")),
  };

  auto parser = parser::Parser(code);
  auto nodes = parser.parse();

  ASSERT_EQ(nodes.size(), expectedNodes.size());
  for(int i =0; i < expectedNodes.size(); i++){
    ASSERT_EQ( *(expectedNodes[i]), *(nodes[i]));
  }
}

TEST(ParserTests, ParseJump){
    const auto code = "JUMP END\n"
                      "END:\n";
    auto expectedNodes = std::array<std::unique_ptr<parser::AST>,2>{
            std::unique_ptr<parser::AST>(new parser::LabelInstr("jump", "end")),
                    std::unique_ptr<parser::AST>(new parser::Label("end"))
    };
    auto nodes = parser::Parser(code).parse();
    ASSERT_EQ(nodes.size(), expectedNodes.size());
    for(int i =0; i < expectedNodes.size(); i++){
        ASSERT_EQ( *(expectedNodes[i]), *(nodes[i]));
    }
}

TEST(ParserTests, ParseAttributes){
  const auto text = "{ stack_size 5 }\n{ mem_size 2 }";
  auto expectedNodes = std::array<std::unique_ptr<parser::AST>, 2>{
      std::unique_ptr<parser::AST>(new parser::Attribute("stack_size", 5)),
      std::unique_ptr<parser::AST>(new parser::Attribute("mem_size", 2)),
  };
  auto nodes = parser::Parser(text).parse();
  std::cout << nodes.size() << std::endl;
  ASSERT_EQ(nodes.size(), expectedNodes.size());
  for(int i =0; i < expectedNodes.size(); i++){
    ASSERT_EQ(*(expectedNodes[i]), *(nodes[i]));
  }
}

#endif
