cmake_minimum_required(VERSION 3.15)
project(RowanVM)

set(CMAKE_CXX_STANDARD 14)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "./bin")

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(Test testDriver.cpp
        ../src/Assembler/Lexer/lexer.cpp lexerTests.hpp
        ../src/Assembler/Parser/parser.cpp parserTests.hpp
        ../src/VirtualMachine/translator.cpp
        ../src/VirtualMachine/vm.cpp)
target_include_directories(Test PUBLIC ../src/Assembler ../src/Assembler/Parser ../src/VirtualMachine ../src)

target_link_libraries(Test ${GTEST_LIBRARIES})