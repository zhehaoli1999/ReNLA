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

}
int main()
{
    hw6_1();
    hw6_2();
}