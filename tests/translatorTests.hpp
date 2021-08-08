#ifndef translator_test_h
#define translator_test_h

#include "gtest/gtest.h"
#include "Lexer/lexer.hpp"
#include "Parser/parser.hpp"
#include "VirtualMachine/Translation/translator.hpp"

bool areEqual(std::string s, std::string s2){
    if(s.size() != s2.size()){
        return false;
    }
    for(int i =0; i < s.size(); i++){

    }
}

TEST(TranslatorTests, TranslateNop){
  auto parser = parser::Parser("nop");
  auto nodes = parser.parse();
  auto translator = translate::Translator();
  auto bin = translator.translate(nodes);
  ASSERT_EQ(std::string(1,9),bin);
}

TEST(TranslatorTests, TranslateCjump){
  auto parser = parser::Parser("LABEL:\nnop\ncjump EQ rb rb LABEL\n");
  auto nodes = parser.parse();
  auto translator = translate::Translator();
  auto bin = translator.translate(nodes).c_str();
  std::array<char, 9> expectedBin = {9,4,0,1,1,0,0,0,0};
  for(int i =0; i < expectedBin.size(); i++){
      ASSERT_EQ(expectedBin[i], bin[i]);
  }
}

TEST(TranslatorTests, TranslateLdc){
  auto parser = parser::Parser("ldc ra 5");
  auto translator = translate::Translator();
  auto bin = translator.translate(parser.parse()).c_str();
  std::array<char, 6> expectedBin = {10,0,5,0,0,0};
  for(int i =0; i < 6; i++){
    ASSERT_EQ(expectedBin[i], bin[i]);
  }
}

#endif
