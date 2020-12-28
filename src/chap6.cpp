//
// Created by 李喆昊 on 2020/12/27.
//
#include "../include/commonHeader.h"
#include "../include/EigenSolver.h"

using namespace ReNLA;

void hw6_1()
{
    cout << "==== hw 6.1 ===="  << endl;
    // x^3 + x^2 -5x + 3 = 0
    Vec p1({3, -5, 1});

    cout << "(i) max abs root: "<< EigenSolver::powerAlg(
            EigenSolver::getFriendMatrixFromPolynomial(p1)
            ).first
            << endl;

    // x^3 - 3x - 1 = 0
    Vec p2({-1, -3, 0});
    cout << "(ii) max abs root: "<< EigenSolver::powerAlg(
            EigenSolver::getFriendMatrixFromPolynomial(p2)
    ).first
         << endl;

    Vec p3({-1000, 790, -99902, 79108.9, 9802.08, 10891.01, 208.01, 101});
    cout << "(iii) max abs root: "<< EigenSolver::powerAlg(
            EigenSolver::getFriendMatrixFromPolynomial(p3)
    ).first
         << endl;
}

void hw6_2()
{
    cout << "==== hw 6.2 ===="  << endl;
    auto p1 = Vec(40).setNum(0.0);
    p1[0] = 1;
    p1[3] = 1;
    auto M = EigenSolver::getFriendMatrixFromPolynomial(p1);
    auto result = EigenSolver::getEigenMatrices(M);
    for(int i = 0; i < result.size(); i++)
    {
        cout << result[i];
    }

    auto A = Matrix({{9.1, 3.0, 2.6, 4.0},
                     {4.2, 5.3, 4.7, 1.6},
                     {3.2, 1.7, 9.4, 0.9},
                     {6.1, 4.9, 3.5, 6.2}});
    cout << "===== x = 0.9 =====" << endl;
    cout << EigenSolver::ImplicitQRDecomposition(A).first;

    cout << "===== x = 1.0 =====" << endl;
    A[{2, 3}] = 1.0;
    cout << EigenSolver::ImplicitQRDecomposition(A).first;

    cout << "===== x = 1.1 =====" << endl;
    A[{2, 3}] = 1.1;
    cout << EigenSolver::ImplicitQRDecomposition(A).first;

}
int main()
{
    hw6_1();
    hw6_2();
}