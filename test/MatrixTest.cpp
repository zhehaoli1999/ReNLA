//
// Created by 李喆昊 on 2020/11/1.
//
#include "../include/Matrix.h"
#include "gtest/gtest.h"

using namespace ReNLA;
//using M = Matrix;

namespace {
    Matrix a = Matrix(3, 3).setIdentity();
    Matrix b = Matrix(3, 3).setTripleDiag(1, 2, 3);
    Matrix h = Matrix(3,3).setHilbert();
    TEST(MatrixTest, construct)
    {
        EXPECT_EQ(a, Matrix({{1, 0, 0},{0, 1,0},{0,0,1}}));
        EXPECT_EQ(b, Matrix({{1, 2, 0},
                                   {3, 1, 2},
                                   {0, 3, 1}})
                   );
        EXPECT_EQ(h, Matrix({ {1.0, 1.0/2.0, 1.0/3.0},
                                   {1.0/2.0, 1.0/3.0, 1.0/4.0},
                                   {1.0/3.0, 1.0/4.0, 1.0/5.0}}));
    }
    TEST(MatrixTest, Transpose)
    {

    }

    TEST(MatrixTest, slice)
    {
        // Slice col vectors
        EXPECT_EQ((b[{0, 2}]), Matrix({{1, 2},{3,1},{0,3}}));

        // row vector slice
        EXPECT_EQ((b[{1, {1, 3}}]), Vec({1,2}));

        // col vector slice
        EXPECT_EQ((b[{{0, 2}, 1}]), Vec({1, 3}));

        // sub-matrix slice
        EXPECT_EQ( (b[{{0,2},{1,3}}]), Matrix({{2, 0},{1,2}}));
    }

    TEST(MatrixTest, add_and_minus)
    {

    }

    TEST(MatrixTest, multiply)
    {

    }

    TEST(MatrixTest, swap)
    {

    }
}
