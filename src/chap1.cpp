//
// Created by 李喆昊 on 2020/10/2.
//
#include "../include/LinearSolver.h"
#include "../include/Matrix.h"
#include "../include/Vec.h"
#include "../include/Timer.h"
#include <iostream>

using namespace std;
using namespace NLA;

void homework1_1()
{
    const int n = 20;
    Matrix A = Matrix(n, n).setTripleDiag(6.0, 1.0, 8.0);
    Vec b(vector<double>(n, 15.0));
    b[0] = 7.0; b[n-1] = 14.0;
    auto S = LinearSolver(A, b);

    Timer t1("basic gauss solve");
    t1.start();
    auto x1 = S.gaussSolve(false);
    t1.end();
    cout << x1;

    Timer t2("column pivot gauss solve");
    t2.start();
    auto x2 = S.gaussSolve(true);
    t2.end();
    cout << x2;
}

int main()
{
    homework1_1();
}