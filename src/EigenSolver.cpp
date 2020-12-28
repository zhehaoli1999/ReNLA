//
// Created by 李喆昊 on 2020/12/27.
//
#include "../include/EigenSolver.h"
#include <cmath>

using namespace ReNLA;

auto& householder = LSSolver::householder; // same to const auto householder = ...

pair<long double, Vec> EigenSolver::powerAlg(const Matrix A) {
    assert(A.rowNum() == A.colNum());
    int n = A.rowNum();
    auto u0 = Vec(n).setOne();
    auto u  = u0;
    long double mu = 0.0;
    auto mu0 = mu;

    int step = 0;
    do{
        mu0 = mu;
        auto y = A * u;
        mu = y.absMax();
        u = y / mu;

        step ++;
        if(step % 1000 == 0)
        {
            cout << mu << endl;
            cout << u;
            cout << u0;
        }
    }while(fabs(mu0 - mu) >= 1e-10);

    return {mu, u.normalize()};
}

Matrix EigenSolver::getFriendMatrixFromPolynomial(const Vec efficients) {
    int n = efficients.size();
    auto m = Matrix(n).setTripleDiag(0.0, 0.0, 1.0);
    for(int i = 0; i < n; i++)
    {
        m[{i, n-1}] = - efficients[ i ];
    }
    return m;
}

pair<Matrix, Matrix> EigenSolver::upHessenberg(Matrix A)
{
    assert(A.colNum() == A.rowNum());
    int n = A.colNum();
    auto Q = Matrix(n).setIdentity();

    for(int k = 0; k <= n-3; k++)
    {
        auto v = householder(A[k][{k+1, n}]);
        auto beta = v[0];
        v[0] = 1.0;

        auto M = beta * Matrix(v) * Matrix(v).transpose();
        assert(M.rowNum() == (n - k - 1));

        auto H = Matrix(M.rowNum()).setIdentity() - M;
        auto H_k = Matrix(n).setIdentity().setSlice({{k+1, n},{k+1,n}}, H);
        Q = Q * H_k;

        A.addToSlice({{k+1, n}, {k, n}}, -M * A[{{k+1, n}, {k, n}}]);
        A.addToSlice({{0,n}, {k+1, n}}, - A[{{0,n}, {k+1, n}}] * M );
    }

    return {A, Q};
}