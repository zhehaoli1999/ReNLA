//
// Created by 李喆昊 on 2020/11/12.
//
#include "../include/LSSolver.h"
#include <cmath>

using namespace ReNLA;

LSSolver::LSSolver(const Matrix& A, const Vec& b) : A{A}, b{b}
{
}

Vec LSSolver::householder(Vec x) {
    int n = x.size();
    x = x / x.normInfin();

    auto sigma =x[{1, n}].dot(x[{1, n}]); //  || x ||^2 - x0^2
    auto v = Vec(n).setSlice(1, n, x[{1, n}]);

    double beta = 0.0;
    if(fabs(sigma - 0.0) < eps) // x is already a one-hot vector
        beta = 0.0;
    else
    {
        auto alpha = sqrt(x[0]*x[0] + sigma); // the length of x
        if(x[0] <= 0)
            v[0] = x[0] - alpha; //  if x[0] <= 0, no need to worry about "near-zero subtraction" problem.
        else
            v[0] = -sigma / (x[0] + alpha); // if x[0] >0, need to consider "near-zero subtraction"

        beta = 2 * v[0]*v[0]  / (sigma + v[0]*v[0]);
        v /= v[0]; // v[0] now is 1.0
    }
    v[0] = beta;
    return v;
}

pair<long double, long double> LSSolver::givens(long double a, long double b) {
    long double c =  0.0;
    long double s =  0.0;
    if(fabs(b) < eps)
    {
        c = 1.0; s = 0.0;
    }
    else
    {
        if(fabs(b) > fabs(a))
        {
            auto t = a / b;
            s = 1 / sqrt(1 + t*t);
            c = s * t;
        }
        else
        {
            auto t = b / a;
            c = 1 / sqrt(1 + t*t);
            s = c*t;
        }
    }
    return {c, s};
}

pair<Matrix, Vec> LSSolver::QRdecomposition(Matrix A) {
    int m = A.shape()[0];
    int n = A.shape()[1];

    auto d = Vec(n);
    for(int j = 0; j < n; j++)
    {
        if(j < m) //TODO: what if j > m ?
        {
            Vec v = LSSolver::householder(A[j][{j, m}]);
            auto beta = v[0];

            v[0] = 1.0; // Note: remember this!
//  below is not recommended :
//            auto I = Matrix(m-j).setIdentity();
//            auto M = I - beta * Matrix({v}) * Matrix({v}).transpose();

            auto w = beta * A[{{j, m},{j, n}}].transpose() * v;
            A.setSlice({{j,m},{j,n}}, A[{{j,m},{j,n}}] - Matrix(v) * Matrix(w).transpose());
            d[j] = beta;
            A[j].setSlice(j+1, m, v[{1,m-j}]);
        }
    }
    return {A, d};
}

Vec LSSolver::QRSolve() {
    int m = A.shape()[0];
    int n = A.shape()[1];
    auto pair = QRdecomposition(A);
    auto R = pair.first;
    auto d = pair.second;
    for(int j = 0; j < n; j++)
    {
        if(j < m) {
            auto beta = d[j];
            auto v = R[j][{j, m}];
            v[0] = 1.0;

            b.setSlice(j, m, b[{j, m}] - beta * v.dot(b[{j, m}]) * v);
        }
    }
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < i and j < n; j++)
        {
            R[{i, j}] = 0.0;
        }
    }

    // We only need the [0 - n] part
    auto c1 = b[{0, n}];
    R = R[{{0, n}, {0, n}}];

    return LinearSolver(R, c1).upTriangleSolve();
}