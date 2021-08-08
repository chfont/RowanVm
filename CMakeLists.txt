cmake_minimum_required(VERSION 3.15)
project(RowanVM)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "./bin")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#Main executable
add_executable(rowan-asm src/asm_main.cpp
        src/VirtualMachine/vm.hpp src/VirtualMachine/vm.cpp
        src/IntermediateData/instruction.hpp
        src/IntermediateData/condition.hpp
        src/Assembler/Lexer/lexer.hpp
        src/Assembler/Lexer/token.hpp
        src/Assembler/Lexer/opcodeToken.hpp
        src/Assembler/Lexer/numberToken.hpp
        src/Assembler/Lexer/registerToken.hpp
        src/Assembler/Lexer/condToken.hpp
        src/Assembler/Lexer/lexer.cpp
        src/Assembler/Lexer/labelToken.hpp
        src/Assembler/Lexer/colonToken.hpp
        src/Assembler/Parser/parser.hpp
        src/Assembler/Parser/ast.hpp
        src/Assembler/Parser/twoRegInstr.hpp
        src/Assembler/Parser/nop.hpp
        src/Assembler/Parser/parser.cpp
        src/Assembler/Parser/labelAst.hpp
        src/Assembler/Parser/singleRegInstr.hpp
        src/Assembler/Parser/registerNumInstr.hpp
        src/Assembler/Parser/condInstr.hpp
        src/VirtualMachine/Translation/translator.hpp
        src/VirtualMachine/Translation/translator.cpp
        src/IntermediateData/emitHex.hpp tests/translatorTests.hpp tests/vmTests.hpp src/Assembler/Parser/labelInstr.hpp src/IntermediateData/opcodeData.hpp)

target_include_directories(rowan-asm PUBLIC src/Assembler/ src/)

add_executable(rowan-vm src/VirtualMachine/vm.cpp src/vm_main.cpp src/VirtualMachine/Parser/VMParser.cpp src/VirtualMachine/Parser/VMParser.hpp src/VirtualMachine/Parser/Executable.cpp src/VirtualMachine/Parser/Executable.hpp)
target_include_directories(rowan-vm PUBLIC src/)