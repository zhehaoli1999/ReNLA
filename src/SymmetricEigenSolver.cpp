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

pair<Matrix, Matrix> SymmetricEigenSolver::thresholdJacobi(Matrix A, bool print_iter_result) {
    assert(A.rowNum() == A.colNum());
    const auto n = A.rowNum();
    const auto sigma = n; // set sigma to n
    auto delta = A.normNonDiag();
    auto J = Matrix(n).setIdentity();
    int k = 0;

    while(delta > 1e-10) {

        if(print_iter_result)
            cout << "k = " << k << ": delta = " << delta << endl;
        k ++;

        // Scan all non-diagonal entries in A
        for (int i = 0; i < n - 1; i++) {
            for (int j = i + 1; j < n; j++) {
                if(fabs(A[{i, j}]) > delta) { // use threshold
                    auto a_pp = A[{i, i}];
                    auto a_qq = A[{j, j}];
                    auto a_pq = A[{i, j}];

                    auto tau = (a_qq - a_pp) / (2 * a_pq);
                    auto sgn_tau = tau > 0.0 ? 1.0 : -1.0;
                    auto t = sgn_tau / (fabs(tau) + sqrt(1 + tau * tau));
                    auto c = 1 / sqrt(1 + t * t);
                    auto s = t * c;
                    auto J_k = Matrix(n).setIdentity();
                    J_k[{i, i}] = c;
                    J_k[{i, j}] = s;
                    J_k[{j, i}] = -s;
                    J_k[{j, j}] = c;

                    A = J_k.transpose() * A * J_k;
                    J = J * J_k;
                }
            }
        }

        bool update_threshold = true;
        for (int i = 0; i < n - 1; i++) {
            for (int j = i + 1; j < n; j++) {
                if(fabs(A[{i, j}]) > delta)
                    update_threshold = false;
            }
        }
        if(update_threshold)
            delta /= sigma; // update threshold
    }

    return {A, J};
}

long double SymmetricEigenSolver::binarySearch(const Matrix &A, const int index) {
    assert(A.rowNum() == A.colNum());
    const auto n = A.rowNum();

    const auto AnormInfin = A.normInfin();
    auto lowerBound = - AnormInfin;
    auto upperBound = AnormInfin;
    const auto eigen_precision  = 1e-6;
    const auto machine_precision = 1e-10;

    vector<long double> x = A.getDiagValue();
    vector<long double> y;
    y.push_back(0.0);
    for (int i = 0; i < n - 1; i++) {
        y.push_back(A[{i, i + 1}]);
    }

    while((upperBound - lowerBound) > eigen_precision)
    {
        auto mid = (upperBound + lowerBound) / 2.0;

        int s = 0;
        auto q = x[0] - mid;
        for(int k = 0; k < n; k++)
        {
            if(q < 0.0)
                s = s+ 1;
            if(k < n-1)
            {
                if(fabs(q) < eps) // q == 0.0
                    q = fabs(y[k+1]) * machine_precision;
                q = x[k+1] - mid - y[k+1] * y[k+1] / q;
            }
        }
        if(s >= index)
            upperBound = mid;
        else
            lowerBound = mid;
    }

    return (upperBound + lowerBound) / 2.0;
}