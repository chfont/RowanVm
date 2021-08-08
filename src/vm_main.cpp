#include "VirtualMachine/vm.hpp"
#include <iostream>
#include <fstream>
#include "VirtualMachine/Parser/VMParser.hpp"

int main(int argc, char* argv[]){
    if (argc != 2) {
        std::cerr << "ERROR: must pass hex file as argument" << std::endl;
        return -1;
    }
    auto file_name = argv[1];
    auto stream = std::ifstream(file_name, std::ifstream::in | std::ifstream::binary);
    if (stream.good()){
        std::string content((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());
        auto parsed = vm::VMParser::parse(content);
        if(parsed.has_value() && parsed.value().isValid()){
            auto vm = vm::VirtualMachine(*parsed.value().binary, *parsed.value().attributes);
            vm.execute();
        }
    } else {
        std::cerr << "ERROR: File not found" << file_name << std::endl;
        return -1;
    }
    return 0;
}


