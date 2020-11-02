//
// Created by 李喆昊 on 2020/10/31.
//

#include "../include/commonHeader.h"

void homework2_1()
{
    cout << "================= HW 2(1) Conditional Num of Hilbert Matrix ===========" << endl;
    for(int i = 5; i<=20; i++)
    {
        auto A = Matrix(i, i).setHilbert();
        cout << "[ i = " << i << " ] ";
        cout << LinearSolver::estimateConditionalNum(A) << endl;
    }
}

void homework2_2()
{
    cout << "================= HW 2(2) Estimated Error vs Real Error ===========" << endl;
    for(int n = 5; n <=30 ; n++)
    {
        auto A = Matrix(n, n);
        for(int i = 0; i < n; i++)
        {
            A[{i,i}] = 1.0;
            A[{i, n-1}] = 1.0;
            for(int j = 0; j < i; j++)
            {
                A[{i, j}] = -1;
            }
        }

        auto x = Vec(n).setRandom(0, 10.0);
        auto b = A * x;
        auto x_calc = LinearSolver(A, b).LUgaussSolve();

        auto r = b - A * x_calc;
        double conditionNum = LinearSolver::estimateConditionalNum(A);
        double relativeError = (x - x_calc).normInfin() / x.normInfin();
        double estimatedError = conditionNum * r.normInfin() / b.normInfin();
        cout << "[ n = "<< n << "] estimated error: " << estimatedError << ", real relative error:" << relativeError << endl;
    }
}

int main()
{
    homework2_1();
    homework2_2();
}