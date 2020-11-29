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
//        cout << a;
        EXPECT_EQ(a, Matrix({{1, 0, 0},{0, 1,0},{0,0,1}}));
//        cout << b;
        EXPECT_EQ(b, Matrix({{1, 2, 0},
                                   {3, 1, 2},
                                   {0, 3, 1}})
                   );
//        cout << h;
        EXPECT_EQ(h, Matrix({ {1.0, 1.0/2.0, 1.0/3.0},
                                   {1.0/2.0, 1.0/3.0, 1.0/4.0},
                                   {1.0/3.0, 1.0/4.0, 1.0/5.0}}));
    }
    TEST(MatrixTest, Transpose)
    {
        EXPECT_EQ(a, a.transpose());
        EXPECT_EQ( b.transpose(), Matrix({{1, 3, 0},
                                         {2, 1, 3},
                                        {0, 2, 1}}));
    }

    TEST(MatrixTest, getSlice)
    {

        // indexing
        EXPECT_EQ((b[{0, 1}]), b[1][0]);
        EXPECT_EQ((b[{0, 1}]), 2);

        // Slice col vectors
        EXPECT_EQ((b[{{0,3},{0, 2}}]), Matrix({{1, 2},{3,1},{0,3}}));

        // row vector slice
        EXPECT_EQ((b[{1, {1, 3}}]), Vec({1,2}));

        // col vector slice
        EXPECT_EQ((b[{{0, 2}, 0}]), Vec({1, 3}));

        // sub-matrix slice
        EXPECT_EQ( (b[{{0,2},{1,3}}]), Matrix({{2, 0},{1,2}}));
    }

    TEST(MatrixTest, setSlice)
    {
        Matrix t = Matrix(3, 3).setIdentity();
        t.setSlice({{0,2},{0,2}}, Matrix({{1,2},{3,4}}));
        EXPECT_EQ(t, Matrix({{1,2,0},
                                   {3,4,0},
                                   {0,0,1}}));

    }

    TEST(MatrixTest, add_and_minus)
    {
        Matrix h_pre = h;
        EXPECT_EQ(h + h, Matrix({ {2.0, 2.0/2.0, 2.0/3.0},
                                  {2.0/2.0, 2.0/3.0, 2.0/4.0},
                                  {2.0/3.0, 2.0/4.0, 2.0/5.0}}));
        EXPECT_EQ(h + 2, Matrix({ {3.0, 1.0/2.0 + 2, 1.0/3.0 + 2},
                                  {1.0/2.0 + 2, 1.0/3.0+2, 1.0/4.0 + 2},
                                  {1.0/3.0 + 2, 1.0/4.0+2, 1.0/5.0 + 2}}));
        h += h;
        EXPECT_EQ(h - h_pre, h_pre);
        EXPECT_EQ( h_pre - 2, Matrix({ {-1.0, 1.0/2.0 - 2, 1.0/3.0 - 2},
                                       {1.0/2.0 -2, 1.0/3.0-2, 1.0/4.0 - 2},
                                       {1.0/3.0 -2, 1.0/4.0-2, 1.0/5.0 - 2}}));
        h -= h_pre;
        EXPECT_EQ(h, h_pre);
    }

    TEST(MatrixTest, multiply)
    {
        EXPECT_EQ(b * a, b);
        EXPECT_EQ( h * 2, Matrix({ {2.0, 2.0/2.0, 2.0/3.0},
                                   {2.0/2.0, 2.0/3.0, 2.0/4.0},
                                   {2.0/3.0, 2.0/4.0, 2.0/5.0}}));
        EXPECT_EQ(b * b, Matrix({{7, 4, 4},
                                            {6, 13, 4},
                                             {9, 6, 7}}));
        EXPECT_EQ(b * Vec({1, 1, 1}), Vec({3, 6, 4}));
    }

    TEST(MatrixTest, swap)
    {
        // TODO
    }

    TEST(MatrixTest, norm)
    {
        EXPECT_EQ(b.normInfin(), 6);
        auto m = Matrix(3, 3).setTripleDiag(-1, 1, -5);
        EXPECT_EQ(m.normInfin(), 7);
    }

    TEST(MatrixTest, inv)
    {
        Matrix A({{1, 0,0},
                     {2,3,0},
                     {4,5,6}});

        auto Ainv = A.lowTriangleInv();
        EXPECT_EQ(Ainv * A, Matrix(3,3).setIdentity());

        Matrix B({{1, 0,0},
                  {0,3,0},
                  {0,0,6}});
        cout << B.lowTriangleInv();
        EXPECT_EQ(B.lowTriangleInv(), Matrix(3).setDiagValue({1, 1.0 /3.0, 1.0 / 6.0}));
    }

    TEST(MatrixTest, diag_L_U)
    {
        Matrix A({{1,2,3},
                     {4,5,6},
                     {7,8,9}});
        auto Adiag = Matrix(3).setDiagValue(A.getDiagValue());
        EXPECT_EQ(Adiag, Matrix({{1,0,0},{0,5,0},{0,0,9}}));
        EXPECT_EQ(A.getLowTriangle(), Matrix({{0,0,0},
                                                        {4,0,0},
                                                        {7,8,0}}));
        EXPECT_EQ(A.getUpTriangle(), Matrix({{0,2,3},
                                                        {0,0,6},
                                                        {0,0,0}}));
    }
}
