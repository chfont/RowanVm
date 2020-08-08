#ifndef parser_test_h
#define parser_test_h

#include "Parser/parser.hpp"
#include "gtest/gtest.h"
#include "Parser/nop.hpp"
#include "Parser/registerNumInstr.hpp"


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

#endif
