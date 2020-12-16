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
  auto vm = vm::VirtualMachine(translator.translate(parser.parse()),translator.getAttributes());
  vm.execute();
  ASSERT_EQ(outputStream.str(), "1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n");
  std::cout.rdbuf(oldBuffer);
}

TEST(VM_Tests, ConstArithTest){
  const auto code = "ldc ra 500\n"
                    "addc ra 52\n"
                    "subc ra 52\n"
                    "divc ra 5\n"
                    "multc ra 2\n"
                    "pr ra";
  std::stringstream outputStream;
  auto oldBuffer =std::cout.rdbuf(outputStream.rdbuf());
  auto parser = parser::Parser(code);
  auto translator = translate::Translator();
  auto vm = vm::VirtualMachine(translator.translate(parser.parse()), translator.getAttributes());
  vm.execute();

  ASSERT_EQ(outputStream.str(), "200\n");
  std::cout.rdbuf(oldBuffer);
}

TEST(VM_Tests, Attributes){
  const auto code = "{ stack_size 5 }\n{ mem_size 2 }";
  auto parser = parser::Parser(code);
  auto translator = translate::Translator();
  auto hex = translator.translate(parser.parse());
  auto vm = vm::VirtualMachine(hex, translator.getAttributes());

  ASSERT_EQ(vm.getMemSize(), 8);
  ASSERT_EQ(vm.getStackSize(), 20);
}

#endif
