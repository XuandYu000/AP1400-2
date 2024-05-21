
#include <iostream>
#include <gtest/gtest.h>
#include "hw1.h"

int main(int argc, char **argv)
{
//     if (true) // make false to run unit-tests
    if(false)
    {
        // debug section
        Matrix matrix2{{1, 2, 3}, {4, 7, 5}, {6, 1, 3}};
        Matrix res2{algebra::upper_triangular(matrix2)};
        algebra::show(matrix2);
        algebra::show(res2);
    }
    else
    {
        ::testing::InitGoogleTest(&argc, argv);
        std::cout << "RUNNING TESTS ..." << std::endl;
        int ret{RUN_ALL_TESTS()};
        if (!ret)
            std::cout << "<<<SUCCESS>>>" << std::endl;
        else
            std::cout << "FAILED" << std::endl;
    }

    return 0;
}