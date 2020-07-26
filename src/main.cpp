#include "Assembler/Lexer/lexer.hpp"
#include "Assembler/Lexer/token.hpp"
#include "vm.hpp"
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

  auto lex = lexer::Lexer(content);
  auto tok = lex.getNextToken();
  while (tok != nullptr) {
    std::cout << tok->emit() << std::endl;
    tok = lex.getNextToken();
  }
  /**auto vm = vm::VirtualMachine(content);
  vm.execute();**/
  return 0;
}