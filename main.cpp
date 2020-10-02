#include <iostream>
#include <vector>
#include "Matrix.h"
#include "Vec.h"
#include "LinearSolver.h"
using namespace std;
using namespace NLA;

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
    Matrix g({{1,2,3},{4,5,6}});
    cout << g;
    cout << g.transpose();
}

void VecTest()
{
    cout << "======= construct ========"<< endl;
    Vec x({1,2,3});
    cout << x;
    cout << "======= slice ========"<< endl;
    cout << x[{0,1}];
    cout << "======= set slice ========"<< endl;
    x.setSlice(1,2, x[{0,1}]);
    cout << x;
    cout << "======= add to slice ========"<< endl;
    x.addToSlice(1,2, -x[{0,1}]);
    cout << x;
    cout << -x;
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
int main() {
    //MatrixTest();
    //VecTest();
    //SolveTest();
    LUtest();
    return 0;
}
