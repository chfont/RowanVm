#include "gtest/gtest.h"
#include "lexerTests.hpp"
#include "parserTests.hpp"
#include "translatorTests.hpp"
#include "vmTests.hpp"

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}



