//
// Created by 李喆昊 on 2020/10/2.
//
#include "../include/LinearSolver.h"
#include "../include/Matrix.h"
#include "../include/Vec.h"
#include "../include/Timer.h"
#include <iostream>
#include <string>

using namespace std;
using namespace NLA;

void solve(Matrix& A, Vec& b, string c)
{
    Timer t(c.c_str());
    auto S = LinearSolver(A, b);
    Vec x(0);
    t.start();
    if(c == "basic gauss solve")
        x = S.LUgaussSolve(false);
    else if(c == "column pivot gauss solve")
        x = S.LUgaussSolve(true);
    else if(c == "Choleskey gauss solve with sqrt used")
        x = S.CholeskeyGaussSolve(false);
    else if(c == "Improved Choleskey gauss solve")
        x = S.CholeskeyGaussSolve(true);
    t.end();
    cout << x;
    cout << "@error: " << (A * x).dist2(b) << endl;
}

void homework1_1()
{
    cout << " ========= HW 1.1 ==========" << endl;
    const int n = 30;
    Matrix A = Matrix(n, n).setTripleDiag(6.0, 1.0, 8.0);
    Vec b(vector<double>(n, 15.0));
    b[0] = 7.0; b[n-1] = 14.0;

    solve(A, b, "basic gauss solve");
    solve(A, b, "column pivot gauss solve");

    cout <<  endl;

}

void homework1_2(Matrix& A1, Vec& b, Matrix& A2, Vec& b2) {
    cout << " ========= HW 1.2 ==========" << endl;
    solve(A1, b, "Choleskey gauss solve with sqrt used");
    solve(A1, b, "Improved Choleskey gauss solve");

    solve(A2, b2, "Choleskey gauss solve with sqrt used");
    solve(A2, b2, "Improved Choleskey gauss solve");

    cout << endl;
}

void homework1_3(Matrix& A1, Vec& b, Matrix& A2, Vec& b2) {
    cout << " ========= HW 1.3 ==========" << endl;
    solve(A1, b, "basic gauss solve");
    solve(A1, b, "column pivot gauss solve");

    solve(A2, b2, "basic gauss solve");
    solve(A2, b2, "column pivot gauss solve");
    cout << endl;
}
int main()
{
    homework1_1();

    const int n = 100;
    Matrix A1 = Matrix(n, n).setTripleDiag(10.0, 1.0, 1.0);
    Vec b = Vec(n).setIncremental();

    const int n2 = 7;
    Matrix A2 = Matrix(n2).setHilbert();
    Vec b2 = A2 * Vec(n2).setOne();
    homework1_2(A1, b,A2,b2);

    homework1_3(A1, b, A2, b2);
}