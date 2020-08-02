#ifndef vmtest_h
#define vmtest_h

#include "Assembler/Parser/parser.hpp"
#include "gtest/gtest.h"
#include <VirtualMachine/translator.hpp>
#include <VirtualMachine/vm.hpp>
TEST(VM_Tests, CounterTest){
  auto code ="ldc ra 10\n"
              "ldc rb 0\n"
              "ldc rc 1\n"
              "LOOP:cjump eq rb ra END\n"
              "add rb rc\n"
              "pr rb\n"
              " cjump eq rc rc LOOP\n"
              "END:";
  std::stringstream outputStream;
  auto oldBuffer =std::cout.rdbuf(outputStream.rdbuf());
  auto parser = parser::Parser(code);
  auto translator = translate::Translator();
  auto vm = vm::VirtualMachine(translator.translate(parser.parse()));
  vm.execute();
  ASSERT_EQ(outputStream.str(), "1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n"); 
  std::cout.rdbuf(oldBuffer);
}

#endif
