//
// Created by 李喆昊 on 2020/11/29.
//

#include "../include/SparseMatrix.h"
#include "gtest/gtest.h"

using namespace ReNLA;

namespace {
    TEST(CRSMatrix, construct)
    {
        Matrix M({{1,0,0,2,0,3},
                    {4,5,0,0,0,0},
                    {0,6,7,0,0,8},
                    {9,0,0,10,11,12},
                    {0,13,0,0,14,0},
                    {0,0,0,0,0,15}});
        vector<int> rowIdx({0,0,0,1,1,2,2,2,3,3,3,3,4,4,5});
        vector<int> colIdx({0,3,5,0,1,1,2,5,0,3,4,5,1,4,5});
        vector<long double> values({1,2,3,4,5,6,7,8,9,10,11,12,13,14,15});
        auto crsM = CRSMatrix(6, 6, rowIdx, colIdx, values).toDense();
        cout << crsM;
        EXPECT_EQ(crsM, M);
    }
}