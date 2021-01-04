//
// Created by 李喆昊 on 2021/1/4.
//
#include "../include/commonHeader.h"
#include "../include/SymmetricEigenSolver.h"
#include "gtest/gtest.h"
#include <cmath>

using namespace ReNLA;

namespace {
    TEST(SymmetricEigenSolverTest, Wilkinson)
    {

    }

    TEST(SymmetricEigenSolverTest, thresholdJacobi)
    {
        auto A = Matrix({ {3, 4, 5},
                             {4, 6, 7},
                             {5, 7, 8}});
        auto resultPair = SymmetricEigenSolver::thresholdJacobi(A, false);
        auto A_ = resultPair.first;
        auto Q = resultPair.second;
        cout << A_;
        cout << Q.transpose() * A * Q;
    }

    TEST(SymmetricEigenSolverTest, binarySearch)
    {
        auto A = Matrix({ {3, 4, 0.0},
                          {4, 6, 7},
                          {0.0, 7, 8}});
        cout << SymmetricEigenSolver::binarySearch(A, 1) << endl;
        cout << SymmetricEigenSolver::binarySearch(A, 2) << endl;
        cout << SymmetricEigenSolver::binarySearch(A, 3) << endl;
    }
}
