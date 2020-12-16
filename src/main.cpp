#include "IntermediateData/emitHex.hpp"
#include "Lexer/lexer.hpp"
#include "Lexer/token.hpp"
#include "Parser/parser.hpp"
#include "VirtualMachine/translator.hpp"
#include "VirtualMachine/vm.hpp"
#include <fstream>
#include <iostream>
int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cout << "ERROR: No argument given" << std::endl;
    return -1;
  }
  auto f = std::ifstream(argv[1]);
  std::string content((std::istreambuf_iterator<char>(f)),
                      (std::istreambuf_iterator<char>()));
    auto parser = parser::Parser(content);
    auto nodes = parser.parse();
    auto translator = translate::Translator();
    auto hex = translator.translate(nodes);
    if(translator.validate_attributes()){
      auto vm = vm::VirtualMachine(hex, translator.getAttributes());
      vm.execute();
    } else {
      std::cout << "Invalid attributes declared" << std::endl;
    }
  return 0;
}