//
// Created by 李喆昊 on 2020/11/27.
//

//
// Created by 李喆昊 on 2020/11/15.
//
#include "../include/IterativeSolver.h"
#include "../include/LinearSolver.h"
#include <cmath>

using namespace ReNLA;
using namespace std;

void solve(const Matrix& A, const Vec& b, const Vec& y=Vec(0))
{
    cout << "========== Jacobi Iter ==========" << endl;
    auto result = IterativeSolver::JacobiIterSolve(A, b);
    cout << "[total step]: " << result.second << endl;
    cout << "[x]: " << result.first;
    if(y.size() > 0)
        cout << "[err]: " << (y - result.first).norm2()<< endl;


//    cout << "========== G-S Iter ==========" << endl;
//    result = IterativeSolver::GaussSeidelIterSolve(A, b);
//    cout << "[total step]: " << result.second << endl;
//    cout << "[x]: " << result.first;
//    if(y.size() > 0)
//        cout << "[err]: " << (y - result.first).norm2() << endl;
//
//    cout << "========== SOR Iter ==========" << endl;
//    result = IterativeSolver::SORIterSolve(A, b);
//    cout << "[total step]: " << result.second << endl;
//    cout << "[x]: " << result.first;
//    if(y.size() > 0)
//        cout << "[err]: " << (y - result.first).norm2()<< endl;
}

void sparseSolve(const CRSMatrix& A, const Vec& b, const Vec& y=Vec(0))
{
    cout << "========== Sparse Jacobi Iter ==========" << endl;
    auto result = IterativeSolver::sparseJacobiIterSolve(A, b);
    cout << "[total step]: " << result.second << endl;
    cout << "[x]: " << result.first;
    if(y.size() > 0)
        cout << "[err]: " << (y - result.first).norm2()<< endl;

}

void hw4_1(double epsi=1.0) {
    double a = 0.5;
    double n = 100.0;
    auto h = 1.0 / n;

    auto A = Matrix(n - 1).setTripleDiag(-(2 * epsi + h), epsi + h, epsi);
    auto b = Vec(n - 1).setNum(a * h * h);
    b[n - 2] -= (epsi + h);
    auto y = Vec(n - 1);
    for (int i = 0; i < n - 1; i++) {
        auto xi = (i + 1) * h;
        y[i] = (1 - a) / (1 - exp(-1.0 / epsi)) * (1 - exp(-xi / epsi)) + a * xi;
    }

    solve(A, b, y);
}

void hw4_2(int N=20)
{
    double h = 1.0 / N;
    auto g = [](double x, double y){return exp(x * y); };
    auto f = [](double x, double y){return x+y; };

    // Initialization
    auto A = Matrix((N-1) * (N-1));
    auto b = Vec((N-1) * (N-1));
    for (int j = 0; j < N - 1; j++) // y axis
    {
        auto y = (j + 1) * h;
        int baseIdx = j * (N-1);
        for (int i = 0; i < N - 1; i++) // x axis
        {
            auto x = (i + 1) * h;
            int idx = baseIdx + i;

            b[idx] = h * h * f(x, y);

            A[{idx, idx}] = 4 + h * h * g(x, y);
            if (idx >= 1)
                A[{idx, idx - 1}] = -1;
            else
                b[idx] += 1;

            if (idx <= (N - 1) * (N - 1) - 2)
                A[{idx, idx + 1}] = -1;
            else
                b[idx] += 1;

            if (idx >= N)
                A[{idx, idx - N}] = -1;
            else
                b[idx] += 1;

            if (idx <= (N - 1) * (N - 1) - 1 - N)
                A[{idx, idx + N}] = -1;
            else
                b[idx] += 1;
        }
    }

    solve(A, b);
}

void hw4_2_sparse(int N=20)
{
    double h = 1.0 / N;
    auto g = [](double x, double y){return exp(x * y); };
    auto f = [](double x, double y){return x+y; };

    // Initialization
    vector<int> rowIdx;
    vector<int> colIdx;
    vector<long double> values;
    int size = (N-1) * (N-1);
    auto b = Vec(size);
    for (int j = 0; j < N - 1; j++) // y axis
    {
        auto y = (j + 1) * h;
        int baseIdx = j * (N-1);
        for (int i = 0; i < N - 1; i++) // x axis
        {
            auto x = (i + 1) * h;
            int idx = baseIdx + i;

            b[idx] = h * h * f(x, y);

            rowIdx.push_back(idx);
            colIdx.push_back(idx);
            values.push_back(4 + h * h * g(x, y));

            if (idx >= 1)
            {
                rowIdx.push_back(idx);
                colIdx.push_back(idx-1);
                values.push_back(-1);
            }
            else
                b[idx] += 1;

            if (idx <= (N - 1) * (N - 1) - 2)
            {
                rowIdx.push_back(idx);
                colIdx.push_back(idx+1);
                values.push_back(-1);
            }
            else
                b[idx] += 1;

            if (idx >= N)
            {
                rowIdx.push_back(idx);
                colIdx.push_back(idx-N);
                values.push_back(-1);
            }
            else
                b[idx] += 1;

            if (idx <= (N - 1) * (N - 1) - 1 - N)
            {
                rowIdx.push_back(idx);
                colIdx.push_back(idx+N);
                values.push_back(-1);
            }
            else
                b[idx] += 1;
        }
    }

    sparseSolve(CRSMatrix(size, size, rowIdx, colIdx, values), b);
}

int main() {
//    hw4_1(1.0);
//    hw4_1(0.1);
//    hw4_1(0.01);
//    hw4_1(0.0001);

//    hw4_2(20);
    hw4_2_sparse(80);
}