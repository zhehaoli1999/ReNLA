//
// Created by 李喆昊 on 2020/10/2.
//

#include "../include/LinearSolver.h"
#include <cmath>

using namespace NLA;

LinearSolver::LinearSolver(Matrix &A, Vec &b) : A{A}, b{b}
{
    // require A to be a square matrix
    assert(A.shape()[0] == A.shape()[1]); // TODO
    assert(A.shape()[0] == b.size());
}

Vec LinearSolver::lowTriangleSolve(bool isDiagAllOne) {
    Vec x = b;
    int n = b.size();
    for(int j = 0; j < n; j++) {
        if(!isDiagAllOne) {
            assert(fabs(A[{j,j}] -0.0) > 1e-6);
            x[j] = x[j] / A[{j, j}];
        }
        x.addToSlice(j+1, n, -A[j][{j+1, n}] * x[j]);
    }
    if(!isDiagAllOne) {
        assert(fabs(A[{n-1, n-1}] - 0.0) > 1e-6);
        x[n - 1] /= A[{n - 1, n - 1}];
    }return x;
}

Vec LinearSolver::upTriangleSolve() {
    Vec x = b;
    int n = b.size();
    for(int j = n-1; j>=1; j--)
    {
        assert(fabs(A[{j,j}] -0.0) > 1e-6);
        x[j] = x[j] / A[{j,j}];
        x.addToSlice(0, j, - A[j][{0, j}] * x[j]);
    }
    assert(fabs(A[{0,0}] -0.0) > 1e-6);
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
          assert(fabs(A[{k,k}] - 0.0) > 1e-6);
          A[k].mulToSlice(k+1, n, 1.0 / A[{k,k}]);
          for(int j = k+1; j < n; j++)
          {
              A[j].addToSlice(k+1, n, - A[k][{k+1, n}] * A[{k,j}]);
          }
    }
    return A;
}

Matrix LinearSolver::LUdecomposeColPivot(Matrix &m, vector<pair<int, int>> &P) {
    Matrix A = m;
    assert(A.shape()[0] == A.shape()[1]);
    int n = A.shape()[0];
    P.clear();
    for(int k =0; k < n; k++)
    {
        auto maxIdx = A[k].maxAbsIdx(k, n); // Note: only select absmax in [k, n] rows
        if( maxIdx != k)
        {
           A.swapRow(maxIdx, k);
           P.emplace_back(maxIdx, k);
        }
        if(fabs(A[{k,k}] - 0.0) >= 1e-6)
        {
            A[k].mulToSlice(k+1, n, 1.0 / A[{k,k}]);
            for(int j = k+1; j < n; j++)
            {
                A[j].addToSlice(k+1, n, - A[k][{k+1, n}] * A[{k,j}]);
            }
        }
        else
        {
            cout << "[Error] Matrix is singular and cannot be LU decomposed. ";
            exit(1);
        }
    }
    return A;
}

Vec LinearSolver::gaussSolve(bool isColPivot) {
    if(!isColPivot)
    {
        Matrix M = LUdecompose(this->A);
        Vec y = LinearSolver(M, b).lowTriangleSolve(true);
        Vec x = LinearSolver(M, y).upTriangleSolve();
        return x;
    }
    else
    {
        vector<pair<int, int>> P;
        Matrix M = LUdecomposeColPivot(this->A, P);
        for(int i = 0; i < P.size(); i++)
        {
            b.swap(P[i].first, P[i].second);
        }
        Vec y = LinearSolver(M, b).lowTriangleSolve(true);
        Vec x = LinearSolver(M, y).upTriangleSolve();
        return x;
    }
}