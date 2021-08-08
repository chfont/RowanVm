#include "Lexer/token.hpp"
#include "Parser/parser.hpp"
#include "VirtualMachine/Translation/translator.hpp"
#include <fstream>
#include <iostream>


std::string getOutputName(std::string input_file_name){
    auto it = std::find(input_file_name.begin(), input_file_name.end(), '.');
    if (it == input_file_name.begin()){
        return "." + getOutputName(input_file_name.substr(1, input_file_name.length()-1));
    } else if (it == input_file_name.end()){
        return input_file_name + ".rwn";
    } else {
        return std::string(input_file_name.begin(), it) + ".rwn";
    }
}

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
        translator.writeToFile(getOutputName(std::string(argv[1])));
    } else {
      std::cout << "Invalid attributes declared" << std::endl;
    }
  return 0;
}