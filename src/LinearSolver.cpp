//
// Created by 李喆昊 on 2020/10/2.
//

#include "../include/LinearSolver.h"
#include <cmath>

using namespace ReNLA;

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
            assert(fabs(A[{j,j}] -0.0) > eps);
            x[j] = x[j] / A[{j, j}];
        }
        x.addToSlice(j+1, n, -A[j][{j+1, n}] * x[j]);
    }
    if(!isDiagAllOne) {
        assert(fabs(A[{n-1, n-1}] - 0.0) > eps);
        x[n - 1] /= A[{n - 1, n - 1}];
    }return x;
}

Vec LinearSolver::upTriangleSolve() {
    Vec x = b;
    int n = b.size();
    for(int j = n-1; j>=1; j--)
    {
        assert(fabs(A[{j,j}] -0.0) > eps);
        x[j] = x[j] / A[{j,j}];
        x.addToSlice(0, j, - A[j][{0, j}] * x[j]);
    }
    assert(fabs(A[{0,0}] -0.0) > eps);
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
          assert(fabs(A[{k,k}] - 0.0) > eps);
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
        auto maxIdx = A[k].maxAbsIdx(k, n); // Note: only select absmax in [k, n-1] rows
        if( maxIdx != k)
        {
           A.swapRow(maxIdx, k);
           P.emplace_back(maxIdx, k);
        }
        if(fabs(A[{k,k}] - 0.0) >= eps)
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

Vec LinearSolver::LUgaussSolve(bool isColPivot) {
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
        for(auto & i : P)
        {
            b.swap(i.first, i.second);
        }
        Vec y = LinearSolver(M, b).lowTriangleSolve(true);
        Vec x = LinearSolver(M, y).upTriangleSolve();
        return x;
    }
}

Matrix LinearSolver::CholeskyDecompose(Matrix &m, bool isImproved) {
    Matrix A = m;
    assert(A.shape()[0] == A.shape()[1]); // TODO: should check A is positive definite
    int n = A.shape()[0];
    if(!isImproved) {
        for (int k = 0; k < n; k++) {
            A[{k, k}] = sqrt(A[{k, k}]);
            A[k].mulToSlice(k + 1, n, 1.0 / A[{k, k}]);
            for (int j = k + 1; j < n; j++) {
                A[j].addToSlice(j, n, -A[k][{j, n}] * A[{j, k}]);
            }
        }
        // Store L in the low triangle part of A
    } else{
        Vec v(n);
        for(int j = 0; j < n; j++)
        {
            for(int i = 0; i <= j-1; i++)
            {
                v[i] = A[{j, i}] * A[{i, i}];
            }
            A[{j,j}] -= A[{j, {0, j}}].dot(v[{0, j}]);
            // The below for loop can be replaced by Matrix * Vec.
            for(int k = 0; k <= j-1; k++)
            {
                A[j].addToSlice(j+1, n, - A[{ {j+1, n}, k}] * v[k]);
            }
            A[j].mulToSlice(j+1, n, 1.0 / A[{j,j}]);
        }
        // Store L in the low triangle part of A and D on the diag of A
    }
    return A;
}

Vec LinearSolver::CholeskeyGaussSolve(bool isImproved) {
    Matrix M = CholeskyDecompose(A, isImproved);
    if(!isImproved) {
        // If isImproved, should set isDiagAllOne to be true when doing lowTriangleSolve.
        Vec y = LinearSolver(M, b).lowTriangleSolve(false);
        Matrix Mt = M.transpose();
        Vec x = LinearSolver(Mt, y).upTriangleSolve();
        return x;
    } else
    {
        Vec y = LinearSolver(M, b).lowTriangleSolve(true);
        Matrix Mt = M.transpose();
// Below is not recommended:
//        for(int i = 0; i < y.size(); i++)
//        {
//            y[i] /= Mt[{i,i}];
//        }
        for(int i = 0; i < Mt.shape()[0]; i++)
        {
            for(int j = i+1; j < Mt.shape()[1]; j++)
            {
                Mt[{i, j}] *= Mt[{i,i}];
            }
        }
        Vec x = LinearSolver(Mt, y).upTriangleSolve();
        return x;
    }
}