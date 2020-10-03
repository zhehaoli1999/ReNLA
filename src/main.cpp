#include <iostream>
#include <vector>
#include "../include/Matrix.h"
#include "../include/Vec.h"
#include "../include/LinearSolver.h"
#include "../include/Timer.h"
using namespace std;
using namespace ReNLA;

void MatrixTest()
{
    Matrix a = Matrix(3,3).setIdentity();
    Matrix b = Matrix(3, 3).setTripleDiag(1,2,3);
    cout << "======== a,b ========"<< endl;
    cout << a;
    cout << b;
    cout << b[{1,2}] << b[2][1] << endl;
    cout << b[{1,0}]<< endl;
    cout << "======== b * b ========"<< endl;
    cout << b * b;
    cout << "======== b + b ========"<< endl;
    cout << b + b;
    cout << "=======b + 100========"<< endl;
    cout << b + 100.0;
    cout << "=======b * 100========"<< endl;
    cout << b * 100.0;
    cout << "======= construct ========"<< endl;
    Matrix g({{1,2,3,4,5},{6,7,8,9,0},{1,2,3,4,5}});
    cout << g;
    cout << g.transpose();
    cout << "======= slice ========"<< endl;
    auto u = g.transpose();
    cout << g.transpose()[{{0,3},1}];
    cout << g.transpose()[{1, {0,2}}];
    cout << g.transpose()[{{1,4}, {1,3}}];
}

void VecTest()
{
    cout << "======= construct ========"<< endl;
    Vec x({1,2,3});
    cout << x;
    cout << "======= slice ========"<< endl;
    cout << x[{0,2}];
    cout << "======= set slice ========"<< endl;
    x.setSlice(1,3, x[{0,2}]);
    cout << x;
    cout << "======= add to slice ========"<< endl;
    x.addToSlice(1,3, -x[{0,2}]);
    cout << x;
    cout << -x;
    cout << "======= mul to slice ========"<< endl;
    x.mulToSlice(1,3, 3);
    cout << x;
    cout << -x;
    cout << "======= max & min ========"<< endl;
    cout << x.maxIdx(0, 3);
    cout << x.minIdx(0,3);
    cout << "======= swap ========"<< endl;
    cout << x.swap(0,1);
    cout << "======= dot ========"<< endl;
    cout << Vec({1,2,3}).dot(Vec({5,6,7}));
}

void SolveTest()
{
    Matrix A = Matrix(3,3).setTripleDiag(2,0,1);
    Vec b({1,2,3});
    LinearSolver S(A, b);
    cout << "======= A ========"<< endl;
    cout << A;
    cout << "======= b ========"<< endl;
    cout << b;
    cout << "======= low triangle solver result ========"<< endl;
    cout << S.lowTriangleSolve();
}

void LUtest()
{
    Matrix A = Matrix(3,3).setTripleDiag(2,3,1);
    cout << A;
    cout << LinearSolver::LUdecompose(A);
}

void gaussTest()
{
    Matrix A = Matrix(3,3).setTripleDiag(2,3,1);
    Vec b({1,2,3});
    cout << "======= A ========"<< endl;
    cout << A;
    cout << "======= b ========"<< endl;
    cout << b;
    cout << "======= gauss solver result ========"<< endl;
    cout << LinearSolver(A,b).LUgaussSolve(false);
    cout << "======= gauss solver result with column pivot ========"<< endl;
    cout << LinearSolver(A,b).LUgaussSolve();
}

void LUgaussPerf()
{
    const int n = 1000;
    Matrix A = Matrix(n, n).setTripleDiag(10.0, 1.0, 1.0);
    Vec b(vector<double>(n, 12.0));
    b[0] = 11.0;
    b[n - 1] = 11.0;

    auto S = LinearSolver(A, b);

    Timer t1("basic gauss solve");
    t1.start();
    auto x1 = S.LUgaussSolve(false);
    t1.end();
    cout << x1;

    Timer t2("col pivot gauss solve");
    t2.start();
    auto x2 = S.LUgaussSolve(true);
    t2.end();
    cout << x2;
}

//int main() {
//    MatrixTest();
//    VecTest();
//    //SolveTest();
//    //LUtest();
//    //gaussTest();
//    //LUgaussPerf();
//    return 0;
//}
