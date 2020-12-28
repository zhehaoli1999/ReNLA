//
// Created by 李喆昊 on 2020/12/27.
//
#include "../include/EigenSolver.h"
#include <cmath>
#include <algorithm>
#include <utility>

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

pair<Matrix, Matrix> EigenSolver::FrancisQRIter(Matrix H) {
    assert(H.rowNum() == H.colNum());
    int N = H.rowNum();
    int n = N -1;
    int m = n - 1;

    auto s = H[{m,m}] + H[{n, n}];
    auto t = H[{m,m}]*H[{n,n}] - H[{m, n}] * H[{n,m}];
    auto x = H[{0,0}]*H[{0,0}] + H[{0,1}]*H[{1,0}]
            - s * H[{0,0}] + t;
    auto y = H[{1,0}] * (H[{0,0}] + H[{1,1}] - s);
    auto z = H[{1,0}] * H[{2,1}];

    auto P = Matrix(N).setIdentity();

    for(int k = -1; k <= N-4; k++)
    {
        auto v = householder(Vec({x, y, z}));
        auto beta = v[0];
        v[0] = 1;

        auto q = max(0, k);
        auto M = beta * Matrix(v) * Matrix(v).transpose();

        // Record P_k
        auto Msize = M.rowNum();
        assert(Msize == 3);
        auto P_k = Matrix(N).setIdentity()
                    .setSlice({{k+1, k+4},{k+1, k+4}},
                                Matrix(Msize).setIdentity() - M);
        P = P * P_k;

        H.addToSlice({{k+1, k+4}, {q, N}}, -M * H[{{k+1, k+4}, {q, N}}]);
        auto r = min(k+4, N-1);
        H.addToSlice({{0, r+1},{k+1, k+4}}, - H[{{0, r+1},{k+1, k+4}}] * M);
        x = H[{k+2, k+1}];
        y = H[{k+3, k+1}];
        if(k < N-4)
            z = H[{k+4, k+1}];
    }

    auto v = householder(Vec({x, y}));
    auto beta = v[0];
    v[0] = 1.0;
    auto M = beta * Matrix(v) * Matrix(v).transpose();
    H.addToSlice({{N-2, N}, {N-3, N}}, - M * H[{{N-2, N}, {N-3, N}}]);
    H.addToSlice({{0,N}, {N-2, N}}, - H[{{0,N}, {N-2, N}}] * M);
    auto P_k = Matrix(N).setIdentity()
            .setSlice({{N-2, N},{N-2, N}},
                      Matrix(2).setIdentity() - M);
    P = P * P_k; // TODO

    return {H, P};
}

pair<Matrix, Matrix> EigenSolver::ImplicitQRDecomposition(Matrix A) {
    assert(A.colNum() == A.rowNum());

    // 1. upHessenberg
    auto upHessenbergPair = EigenSolver::upHessenberg(std::move(A));
    auto H = upHessenbergPair.first;
    auto Q = upHessenbergPair.second;

    // 2. Check convergence
    while(true) {
        if (EigenSolver::ImplicitQRConvergenceCheck(H, Q))
            break;
    }
    return {H, Q};

}

bool EigenSolver::ImplicitQRConvergenceCheck(Matrix &H, Matrix &Q) {
    const int n = H.rowNum();
    using Slice = pair<pair<int, int>, pair<int, int>>;
    const auto u = 1e-10; // prescribed machine precision

    for (int i = 1; i < n; i++) {
        if (fabs(H[{i, i - 1}]) <= (fabs(H[{i, i}]) + fabs(H[{i - 1, i - 1}])) * u) {
            H[{i, i - 1}] = 0.0;
        }
    }
    int m = 0;
    for (int i = n - 1; i >= 1; i--) {
        // sub-diag entry is 0
        if (fabs(H[{i, i - 1}] - 0.0) < u) {
            m++;
            if(i == 1)
            {
                m++;
            }
        }
        else // sub-diag entry is not 0
        {
            //  x  x  x  (x --> not 0)
            //     x  x
            if (i >= 2 && fabs(H[{i - 1, i - 2}] - 0.0) > u)
                break;
            else {
                auto a = H[{i - 1, i - 1}];
                auto b = H[{i - 1, i}];
                auto c = H[{i, i - 1}];
                auto d = H[{i, i}];
                auto delta = (a - d) * (a - d) + 4 * b * c;
                if (delta < 0)
                    m++;
                else break;
            }
        }
    }

    int l = 0;
    for (int i = n - 1 - m; i >= 0; i--) {
        //  x x
        //  0 x  happens
        if (i >= 1 && fabs(H[{i, i - 1}] - 0.0) < u) {
            l = i;
            break;
        }
        else
            continue;
    }

    cout << "m: " << m << endl;
    cout << "l: " << l << endl;

    assert( m >=0 && m <= n);
    assert( l >=0 && l <= n);

    if(m == n)
        return true;
    else
    {
        if(n -m > l) {
            auto H22_slice = Slice{{l, n - m},
                                   {l, n - m}};

            auto H22 = H[H22_slice];
            auto FrancisPair = EigenSolver::FrancisQRIter(H22); // H22.rowNum() should > 2!
            auto H22_ = FrancisPair.first;
            auto P = FrancisPair.second;
            H.setSlice(H22_slice, H22_);
            Q = Q * Matrix(Q.rowNum()).setIdentity().setSlice(H22_slice, P);

            if(l > 0)
            {
                auto H12_slice = Slice{{0, l},{l, n-m}};
                H.setSlice(H12_slice, H[H12_slice] * P);
            }
            if(n > n-m)
            {
                auto H23_slice = Slice{{l, n-m},{n-m, n}};
                H.setSlice(H23_slice,P.transpose() * H[H23_slice]);
            }
        }

        return false;
    }


}