cmake_minimum_required(VERSION 3.15)
project(RowanVM)

set(CMAKE_CXX_STANDARD 14)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "./bin")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

#Main executable
add_executable(RowanVM src/main.cpp
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
        src/VirtualMachine/translator.hpp
        src/VirtualMachine/translator.cpp
        src/IntermediateData/emitHex.hpp tests/translatorTests.hpp tests/vmTests.hpp src/Assembler/Parser/labelInstr.hpp src/IntermediateData/opcodeData.hpp)

target_include_directories(RowanVM PUBLIC src/Assembler/ src/)