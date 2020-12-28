//
// Created by 李喆昊 on 2020/12/8.
//
#include "../include/IterativeSolver.h"
#include "../include/LinearSolver.h"
#include <cmath>

using namespace ReNLA;
using namespace std;

void hw5_1()
{
    const int N = 20;
    cout << "==== hw 5.1 (n = "<< N << ") ====" << endl;
    const double h = 1.0 / N;
    auto f = [](double x, double y){return sin(x*y);};
    auto phi = [](double x, double y){return x*x + y*y; };

    // Initialization
    vector<int> rowIdx;
    vector<int> colIdx;
    vector<long double> values;
    int size = (N-1) * (N-1);
    auto b = Vec(size);

    // TODO : fix bug of this function.
    // Traverse all nodes in grid
    for (int j = 0; j < N - 1; j++) // y axis
    {
        auto y = (j + 1) * h;
        int baseIdx = j * (N-1);
        for (int i = 0; i < N - 1; i++) // x axis
        {
            auto x = (i + 1) * h;
            int idx = baseIdx + i;

            b[idx] = h * h * f(x, y) / 4.0;

            rowIdx.push_back(idx);
            colIdx.push_back(idx);
            values.push_back(1 + h * h / 4.0);

            if (idx >= 1)
            {
                rowIdx.push_back(idx);
                colIdx.push_back(idx-1);
                values.push_back(-1.0 / 4.0);
            }
            else
                b[idx] += phi(0.0, y) / 4.0;

            if (idx <= (N - 1) * (N - 1) - 2)
            {
                rowIdx.push_back(idx);
                colIdx.push_back(idx+1);
                values.push_back(-1.0 / 4.0);
            }
            else
                b[idx] += phi(1.0, y) / 4.0;

            if (idx >= N)
            {
                rowIdx.push_back(idx);
                colIdx.push_back(idx-N);
                values.push_back(-1.0 / 4.0);
            }
            else
                b[idx] += phi(x, 0.0) / 4.0;

            if (idx <= (N - 1) * (N - 1) - 1 - N)
            {
                rowIdx.push_back(idx);
                colIdx.push_back(idx+N);
                values.push_back(-1.0 / 4.0);
            }
            else
                b[idx] += phi(x, 1.0) / 4.0;
        }
    }

    auto A = CSRMatrix(size, size, rowIdx, colIdx, values);

    cout << "====== CG ======" << endl;
    Timer t1("CG iteration");
    t1.start();
    auto result = IterativeSolver::sparseCGIterSolve(A, b);
    t1.end();
    auto x_CG = result.first;
    auto step = result.second;
    cout << "step: " << step << endl;
    cout << x_CG;

    cout << "===== SOR =====" << endl;
    Timer t2("SOR iteration");
    t2.start();
    auto result_SOR = IterativeSolver::sparseSORIterSolve(A, b, 1.795);
    t2.end();
    auto x_SOR = result_SOR.first;
    auto step_SOR = result_SOR.second;
    cout << "step: " << step_SOR << endl;
    cout << x_SOR;
}

void hw5_2()
{
    const int n = 80;
    cout << "==== hw 5.2 (n = " << n <<") ====" << endl;

    Matrix A = Matrix(n).setHilbert();
    Vec b = 1.0/3.0 * A * Vec(n).setOne();

    cout << "====== CG ======" << endl;
    Timer t1("CG iteration");
    t1.start();
    auto result = IterativeSolver::CGIterSolve(A, b);
    t1.end();
    auto x_CG = result.first;
    auto step = result.second;
    cout << "step: " << step << endl;
    cout << x_CG;

    cout << "====== G-S ======" << endl;
    Timer t2("G-S iteration");
    t2.start();
    auto result_GS = IterativeSolver::GaussSeidelIterSolve(A, b);
    t2.end();
    auto x_GS = result_GS.first;
    auto step_GS = result_GS.second;
    cout << "step: " << step_GS << endl;
    cout << x_GS;

    cout << "====== linear solver =====" << endl;
    auto x_linear = LinearSolver(A, b).LUgaussSolve();
    cout << x_linear;

    auto ans = Vec(n).setNum(1.0/ 3.0);
    cout << "CG err: " << (ans-x_CG).norm2() << endl;
    cout << "G-S err: " << (ans-x_GS).norm2() << endl;
    cout << "LUguass err: " << (ans-x_linear).norm2() << endl;

}

void hw5_3()
{
    cout << "==== hw 5.3 ====";
    auto A = Matrix({{10, 1, 2,3,4},
                     {1, 9, -1, 2, -3},
                     {2, -1, 7, 3, -5},
                     {3, 2, 3, 12 ,-1},
                     {4, -3, -5, -1, 15}});
    auto b = Vec({12, -27, 14, -17, 12});

    cout << "====== CG ======" << endl;
    auto result_CG =IterativeSolver::CGIterSolve(A, b);
    auto x_CG = result_CG.first;
    auto step_CG = result_CG.second;
    cout << "step: " << step_CG << endl;
    cout << x_CG;
    cout << "====== G-S ======" << endl;
    auto result_GS = IterativeSolver::GaussSeidelIterSolve(A, b);
    auto x_GS = result_GS.first;
    auto step_GS = result_GS.second;
    cout << "step: " << step_GS << endl;
    cout << x_GS;
    cout << "====== Jacobi ======" << endl;
    auto result_J =  IterativeSolver::JacobiIterSolve(A, b);
    auto x_J = result_J.first;
    auto step_J = result_J.second;
    cout << "step: " << step_J << endl;
    cout << x_J;
}

int main()
{
    hw5_1();
    hw5_2();
    hw5_3();
}
