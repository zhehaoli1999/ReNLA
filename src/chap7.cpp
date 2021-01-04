//
// Created by 李喆昊 on 2021/1/4.
//
#include "../include/commonHeader.h"
#include "../include/SymmetricEigenSolver.h"
#include <algorithm>

using namespace std;

void hw7_1()
{
    cout << "==== hw 7.1 ====" << endl;
    auto v = vector<int>({50, 60, 70, 80, 90, 100});
    for(auto n : v) {
        cout << "===== n = " << n << " ========" << endl;
        auto A = Matrix(n).setTripleDiag(4.0, 1.0, 1.0);
        auto A_ = SymmetricEigenSolver::thresholdJacobi(A).first;
        auto diags = A_.getDiagValue();
        sort(diags.begin(), diags.end());
        cout << "==== Eigen Value ====" << endl;
        for (auto i: diags) {
            cout << i << endl;
        }
        cout << endl;
    }
}

void hw7_2()
{
    cout << "==== hw 7.2 ====" << endl;
    auto A = Matrix(100).setTripleDiag(2.0, -1.0, -1.0);
    cout << "Minimal eigen value = " << SymmetricEigenSolver::binarySearch(A, 1) << endl;
    cout << "Max eigen value = " << SymmetricEigenSolver::binarySearch(A, 100) << endl;
}

int main()
{
    hw7_1();
    hw7_2();
}

