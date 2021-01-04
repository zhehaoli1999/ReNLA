//
// Created by 李喆昊 on 2020/11/15.
//
#include "../include/LSSolver.h"
#include "gtest/gtest.h"
#include <cmath>

using namespace ReNLA;

namespace
{
    TEST(LSSolverTest, householder)
    {
        Vec x1({2.0, 0.0, 0.0, 0.0, 0.0});
        auto v1 = LSSolver::householder(x1);
        EXPECT_EQ(v1, Vec({0.0, 0.0, 0.0,0.0,0.0}));

        Vec x2({2.0, 3.0, 4.0, 5.0, 6.0});
        auto sigma = (9.0 + 16.0 + 25.0 + 36.0) * (1.0 / 36.0);
        auto alpha = sqrt(4.0 / 36.0 + sigma);
        auto t = - sigma / (2.0 / 6.0 + alpha);

        auto v2 = LSSolver::householder(x2);
        auto beta = 2 * t * t / (sigma + t * t);
        EXPECT_EQ(v2[0],  beta);
        EXPECT_LE((v2[{1, 5}] -  Vec({3.0, 4.0, 5.0, 6.0}) / 6.0 / t).normInfin(), 1e-10);

        beta = v2[0];
        v2[0] = 1.0;
        Matrix H = Matrix(5).setIdentity() -  beta * Matrix({v2}) * Matrix({v2}).transpose();
        EXPECT_LE((H * x2 -Vec(5).setOneHot(0) * x2.norm2()).normInfin(), 1e-10);

        Vec x3({0.00001, 300.0, 400.0, 500.0, 600.0});
        auto v3 = LSSolver::householder(x3);
        auto beta3 = v3[0];
        v3[0] = 1.0;
        Matrix H3 = Matrix(5).setIdentity() -  beta3 * Matrix({v3}) * Matrix({v3}).transpose();
        EXPECT_LE((H3 * x3 - Vec(5).setOneHot(0) * x3.norm2()).normInfin(), 1e-10);
    }

    TEST(LSSolverTest, Givens)
    {
        auto a = 3.0;
        auto b = 4.0;

        auto cs = LSSolver::givens(a, b);
        auto c = cs.first;
        auto s = cs.second;
        cout << "c: "<< c << endl;
        cout << "s: "<< s << endl;
        cout << Matrix({{c, s}, {-s ,c}}) * Vec({a, b});
    }

    TEST(LSSolverTest, QRdecomposition)
    {
        auto A = Matrix({{1,2,3},
                    {2,3,4},
                    {3,4,5},
                    {4,5,6}});

        auto pair = LSSolver::QRdecomposition(A);
        auto Aprime = pair.first;
        auto d = pair.second;

        /********************* reconstruct Q^T * A *************************/
        auto v0 = Aprime[0][{0,4}];
        v0[0] = 1.0;
        auto beta0 = d[0];
        auto v1 = Aprime[1][{1,4}];
        v1[0] =1.0;
        auto beta1 = d[1];
        auto v2 = Aprime[2][{2,4}];
        v2[0] = 1.0;
        auto beta2 = d[2];

        auto w0 = beta0 * A.transpose() * v0;
        auto A0 = A - Matrix(v0) * Matrix(w0).transpose();

        auto w1 = beta1 * A0[{{1,4},{1,3}}].transpose() * v1;
        auto A1 = A0.setSlice({{1,4},{1,3}},
                A0[{{1,4},{1,3}}] - Matrix(v1) * Matrix(w1).transpose());

        auto w2 = beta2 * A1[{{2,4},{2,3}}].transpose() * v2;
        auto A2 = A1.setSlice( {{2,4},{2,3}},
                A1[{{2,4},{2,3}}] - Matrix(v2) * Matrix(w2).transpose());
        /**********************************************/
        auto R = Aprime;
        for(int i = 0; i < 4; i++)
        {
            for(int j = 0; j < i and j < 3; j++)
            {
                R[{i, j}] = 0;
            }
        }

        EXPECT_LE((A2 - R).normInfin(), 1e-10);
    }

    TEST(LSSolverTest, QRdecomposition2)
    {
        auto A = Matrix({{1.0, 0.5, 0.333333333},
                           {0.5, 0.3333333333, 0.25},
                           {0.3333333333, 0.25, 0.2}});
        auto pair = LSSolver::QRdecomposition(A);
        auto R = pair.first;
        for(int i = 0; i < 3; i++)
        {
            for(int j = 0; j < i and j < 3; j++)
            {
                R[{i, j}] = 0;
            }
        }
        auto answerR = Matrix({{1.166666667, 0.6428571429,           0.45},
                               {          0, 0.1017143303,   0.1053370325},
                               {          0,            0, 0.003901371573}});
        EXPECT_LE((R-answerR).normInfin(), 1e-9);
    }
}
