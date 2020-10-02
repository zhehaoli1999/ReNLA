//
// Created by 李喆昊 on 2020/10/2.
//

#include "LinearSolver.h"

using namespace NLA;

LinearSolver::LinearSolver(Matrix &A, Vec &b) : A{A}, b{b}
{
    // require A to be a square matrix
    assert(A.shape()[0] == A.shape()[1]); // TODO
    assert(A.shape()[0] == b.size());
}

Vec LinearSolver::lowTriangleSolve() {
    Vec x = b;
    int n = b.size();
    for(int j = 0; j < n; j++) {
        x[j] = x[j] / A[{j,j}];
        x.addToSlice(j+1, n, -A[j][{j+1, n}] * x[j]);
    }
    x[n-1] /= A[{n-1, n-1}];
    return x;
}

Vec LinearSolver::upTriangleSolve() {
    Vec x = b;
    int n = b.size();
    for(int j = n-1; j>=0; j--)
    {
        x[j] = x[j] / A[{j,j}];
        x.addToSlice(0, j-1, - A[j][{1, j-1}] * x[j]);
    }
    x[0] /= A[{0,0}];
    return x;
}

Matrix LinearSolver::LUdecompose(Matrix& m) {
    Matrix A = m;
    assert(A.shape()[0] == A.shape()[1]);
    int n = A.shape()[0];
    // without column pivot selecting
    for(int k = 0; k < n; k++)
    {
          A[k].mulToSlice(k+1, n, 1 / A[{k,k}]);
          for(int j = k+1; j < n; j++)
          {
              A[j].addToSlice(k+1, n, - A[k][{k+1, n}] * A[{k,j}]);
          }
    }
    return A;
}

Matrix LinearSolver::LUdecomposeColPivot(Matrix &m, Matrix &P) {
    Matrix A = m;
    assert(A.shape()[0] == A.shape()[1]);
    int n = A.shape()[0];
}

Vec LinearSolver::gaussSolve(bool isColPivot) {


}