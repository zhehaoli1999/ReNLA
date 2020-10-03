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
    const int n = 40;
    Matrix A = Matrix(n, n).setTripleDiag(6.0, 1.0, 8.0);
    Vec b(vector<double>(n, 15.0));
    b[0] = 7.0; b[n-1] = 14.0;
    auto S = LinearSolver(A, b);

    Timer t1("basic gauss solve");
    t1.start();
    auto x1 = S.LUgaussSolve(false);
    t1.end();
    cout << x1;

    Timer t2("column pivot gauss solve");
    t2.start();
    auto x2 = S.LUgaussSolve(true);
    t2.end();
    cout << x2;
}

void homework1_2() {
    const int n = 100;
    Matrix A1 = Matrix(n, n).setTripleDiag(10.0, 1.0, 1.0);
    Vec b = Vec(n, 12);
    b[0] = b[n-1] = 11;
    //Vec b = Vec(n).setIncremental();

    auto S1 = LinearSolver(A1, b);

    Timer t1("Choleskey gauss solve with sqrt used");
    t1.start();
    auto x11 = S1.CholeskeyGaussSolve(false);
    t1.end();
    cout << x11;

    Timer t2("Improved Choleskey gauss solve");
    t2.start();
    auto x12 = S1.CholeskeyGaussSolve(true);
    t2.end();
    cout << x12 << endl;

    const int n2 = 5;
    Matrix A2 = Matrix(n2).setHilbert();
    Vec b2 = A2 * Vec(n2).setOne();
    auto S2 = LinearSolver(A2, b2);

    t1.start();
    auto x21 = S2.CholeskeyGaussSolve(false);
    t1.end();
    cout << x21;

    t2.start();
    auto x22 = S2.CholeskeyGaussSolve(true);
    t2.end();
    cout << x22;
}

int main()
{
    //homework1_1();
    homework1_2();
}