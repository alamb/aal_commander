#include "gtest/gtest.h"
#include <iostream>

// Main unit test driver
int main(int argc, char **argv) 
{
    std::cout << "Beginning test execution...." << std::endl;

     ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}