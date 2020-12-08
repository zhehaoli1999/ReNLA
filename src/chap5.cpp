//
// Created by 李喆昊 on 2020/12/8.
//
#include "../include/IterativeSolver.h"
#include "../include/LinearSolver.h"
#include <cmath>

using namespace ReNLA;
using namespace std;

void hw5_1()
{

}

void hw5_2()
{
    cout << "==== hw 5.2 ====";
    const int n = 80;
    Matrix A = Matrix(n).setHilbert();
    Vec b = 1.0/3.0 * A * Vec(n).setOne();

    cout << "====== CG ======" << endl;
    Timer t1("CG iteration");
    t1.start();
    auto result = IterativeSolver::CGIterSolve(A, b);
    t1.end();
    auto x_CG = result.first;
    auto step = result.second;
    cout << "step: " << step << endl;
    cout << x_CG;

    cout << "====== G-S ======" << endl;
    Timer t2("G-S iteration");
    t2.start();
    auto result_GS = IterativeSolver::GaussSeidelIterSolve(A, b);
    t2.end();
    auto x_GS = result_GS.first;
    auto step_GS = result.second;
    cout << "step: " << step_GS << endl;
    cout << x_GS;

    cout << "====== linear solver =====" << endl;
    auto x_linear = LinearSolver(A, b).LUgaussSolve();
    cout << x_linear;

    auto ans = Vec(n).setNum(1.0/ 3.0);
    cout << "CG err: " << (ans-x_CG).norm2() << endl;
    cout << "G-S err: " << (ans-x_GS).norm2() << endl;
    cout << "LUguass err: " << (ans-x_linear).norm2() << endl;

}

void hw5_3()
{
    cout << "==== hw 5.3 ====";
    auto A = Matrix({{10, 1, 2,3,4},
                     {1, 9, -1, 2, -3},
                     {2, -1, 7, 3, -5},
                     {3, 2, 3, 12 ,-1},
                     {4, -3, -5, -1, 15}});
    auto b = Vec({12, -27, 14, -17, 12});

    cout << "====== CG ======" << endl;
    auto result_CG =IterativeSolver::CGIterSolve(A, b);
    auto x_CG = result_CG.first;
    cout << x_CG;
    cout << "====== G-S ======" << endl;
    auto result_GS = IterativeSolver::GaussSeidelIterSolve(A, b);
    auto x_GS = result_GS.first;
    cout << x_GS;
    cout << "====== Jacobi ======" << endl;
    auto result_J =  IterativeSolver::JacobiIterSolve(A, b);
    auto x_J = result_J.first;
    cout << x_J;
}

int main()
{
    hw5_3();
}
