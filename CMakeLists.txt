cmake_minimum_required(VERSION 3.15)
project(RowanVM)

set(CMAKE_CXX_STANDARD 14)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "./bin")
add_executable(RowanVM src/main.cpp src/vm.hpp src/decode.hpp src/vm.cpp src/instruction.hpp src/condition.hpp src/Assembler/assembler.hpp src/Assembler/opcode.hpp src/Assembler/assembler.cpp)