//
// Created by 李喆昊 on 2021/1/4.
//
#include "../include/SymmetricEigenSolver.h"
#include "../include/LSSolver.h"

using namespace ReNLA;
using namespace std;

auto& givens = LSSolver::givens;

pair<Matrix, Matrix> SymmetricEigenSolver::WilkinsonImplicitQRIter(Matrix T) {
    assert(T.rowNum() == T.colNum());
    auto N = T.rowNum();
    auto n = N - 1;

    auto d = (T[{n-1, n-1}] - T[{n, n}]) / 2.0;
    auto sgn_d = d > 0.0 ? 1.0 : -1.0;
    auto mu = T[{n,n}] -
            (T[{n, n-1}] * T[{n, n-1}]) /
             (d + sgn_d * sqrt(d*d + T[{n, n-1}] * T[{n, n-1}]));
    auto x = T[{0, 0}] - mu;
    auto z = T[{1, 0}];

    auto G = Matrix(N).setIdentity();

    for(int k = 0; k <= n-1; k++)
    {
        auto cs = givens(x, z);
        auto c = cs.first;
        auto s = cs.second;

        auto G_k = Matrix(N).setIdentity();
        G_k[{k,k}] = c;
        G_k[{k,k+1}] = s;
        G_k[{k+1,k}] = -s;
        G_k[{k+1,k+1}] = c;

        G = G_k * G;
        T = G_k * T * G_k.transpose();
        if(k < n-1)
        {
            x = T[{k+1, k}];
            z = T[{k+2, k}];
        }
    }

    return {T, G};
}