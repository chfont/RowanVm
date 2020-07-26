#include <iostream>
#include "vm.hpp"
#include <fstream>
int main(int argc, char* argv[]) {
    if(argc < 2){
        std::cout << "ERROR: No argument given" << std::endl;
        return -1;
    }
    auto f = std::ifstream(argv[1], std::ios::binary);
    std::string content( (std::istreambuf_iterator<char>(f) ),
                         (std::istreambuf_iterator<char>()    ) );
    auto vm = vm::VirtualMachine(content);
    vm.execute();
    return 0;
}