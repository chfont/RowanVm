cmake_minimum_required(VERSION 3.15)
project(RowanVM)

set(CMAKE_CXX_STANDARD 14)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "./bin")

#Main executable
add_executable(RowanVM src/main.cpp
        src/vm.hpp src/vm.cpp
        src/instruction.hpp
        src/condition.hpp
        src/Assembler/assembler.hpp
        src/Assembler/opcode.hpp
        src/Assembler/Lexer/lexer.hpp
        src/Assembler/Lexer/token.hpp
        src/Assembler/Lexer/opcodeToken.hpp
        src/Assembler/Lexer/numberToken.hpp
        src/Assembler/Lexer/registerToken.hpp
        src/Assembler/Lexer/condToken.hpp
        src/Assembler/Lexer/lexer.cpp
        src/Assembler/Lexer/labelToken.hpp
        src/Assembler/Lexer/colonToken.hpp)