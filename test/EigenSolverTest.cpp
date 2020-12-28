//
// Created by 李喆昊 on 2020/12/27.
//
#include "../include/commonHeader.h"
#include "../include/EigenSolver.h"
#include "gtest/gtest.h"
#include <cmath>

using namespace ReNLA;

namespace {
    TEST(EigenSolverTest, powerAlg)
    {
        auto A = Matrix({{1, 2,3},
                            {4,5,6},
                            {7,8,9}});

        auto eigenPair = EigenSolver::powerAlg(A);
        auto eigenVal = eigenPair.first;
        auto eigenVec = eigenPair.second;
        cout << "eigen val:" << eigenVal << endl;
        EXPECT_EQ(eigenVal, 16.1168);
        cout << "eigen vec:" << eigenVec << endl;
    }

    TEST(EigenSolverTest, friendMatrix)
    {
        Vec p({3, -5, 1});
        auto m = EigenSolver::getFriendMatrixFromPolynomial(p);
        cout << m;
        EXPECT_EQ(m,
                Matrix({{0, 0, -3},
                             {1, 0, 5},
                             {0, 1, -1}}));
    }

    TEST(EigenSolverTest, upHessenberg)
    {
        auto A = Matrix({{1,2,3},
                         {4,5,6},
                         {7,8,9}});

        auto resultPair = EigenSolver::upHessenberg(A);
        auto H = resultPair.first;
        auto Q = resultPair.second;
        cout << resultPair.first;
        cout << Q.transpose() * A * Q;
    }

    TEST(EigenSolverTest, upHessenberg2) {
        auto A = Matrix({{1.1908,  -1.0565, -2.1707, 0.5913,  0.0000,  0.7310},
                         {-1.2025, 1.4151,  -0.0592, -0.6436, -0.3179, 0.5779},
                         {-0.0198, -0.8051, -1.0106, 0.3803,  1.0950,  0.0403},
                         {-0.1567, 0.5287,  0.6145,  -1.0091, -1.8740, 0.6771},
                         {-1.6041, 0.2193,  0.5077,  -0.0195, 0.4282,  0.5689},
                         {0.2573,  -0.9219, 1.6924,  -0.0482, 0.8956,  -0.2556}});

        auto resultPair = EigenSolver::upHessenberg(A);
        auto H = resultPair.first;
        auto Q = resultPair.second;
        cout << resultPair.first;
        cout << Q.transpose() * A * Q;
    }

}
