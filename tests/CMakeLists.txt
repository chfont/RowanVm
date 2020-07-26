cmake_minimum_required(VERSION 3.15)
project(RowanVM)

set(CMAKE_CXX_STANDARD 14)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "./bin")

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(Test testDriver.cpp ../src/Assembler/Lexer/lexer.cpp lexerTests.hpp)
target_include_directories(Test PUBLIC ../src/Assembler/Lexer)

target_link_libraries(Test ${GTEST_LIBRARIES})