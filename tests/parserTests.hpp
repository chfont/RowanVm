#ifndef parser_test_h
#define parser_test_h

#include "Parser/parser.hpp"
#include "gtest/gtest.h"
#include "Parser/nop.hpp"


TEST(ParserTests, ParseNop){
  const auto code = "nop";
  const auto nopNode = std::unique_ptr<parser::AST>(new parser::Nop());
  auto parser = parser::Parser(code);
  auto nodes = parser.parse();
  ASSERT_EQ(nodes.size(), 1);
  ASSERT_EQ(*(nodes[0]), *nopNode);
}

#endif
