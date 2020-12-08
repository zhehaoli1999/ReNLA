//
// Created by 李喆昊 on 2020/11/15.
//
#include "../include/LSSolver.h"
#include "../include/LinearSolver.h"

using namespace ReNLA;
using namespace std;

void hw3_1_1()
{
    const int n = 84;
    Matrix A = Matrix(n, n).setTripleDiag(6.0, 1.0, 8.0);
    Vec b(vector<long double>(n, 15.0));
    b[0] = 7.0; b[n-1] = 14.0;

    cout << "======== QR solve ========" << endl;
    auto x0 = LSSolver(A, b).QRSolve();
    cout << x0 << "r(x): " << (b - A * x0).norm2() << endl;
    cout << "======== ColPivot Gauss solve ========" << endl;
    auto x1 = LinearSolver(A, b).LUgaussSolve();
    cout << x1 << "r(x): " << (b - A * x1).norm2() << endl;
    cout << endl;
}

void hw3_1_2()
{
    const int n = 100;
    Matrix A = Matrix(n, n).setTripleDiag(10.0, 1.0, 1.0);
    Vec b = Vec(n).setIncremental();

    cout << "======== QR solve ========" << endl;
    auto x0 = LSSolver(A, b).QRSolve();
    cout << x0 << "r(x): " << (b - A * x0).norm2() << endl;
    cout << "======== ColPivot Gauss solve ========" << endl;
    auto x1 = LinearSolver(A, b).LUgaussSolve();
    cout << x1 << "r(x): " << (b - A * x1).norm2() << endl;
    cout << "======== Improved Cholesky solve ========" << endl;
    auto x2 = LinearSolver(A, b).CholeskeyGaussSolve();
    cout << x2 << "r(x): " << (b - A * x2).norm2() << endl;
    cout << endl;
}

void hw3_1_3()
{
    const int n2 = 40;
    Matrix A = Matrix(n2).setHilbert();
    Vec b = A * Vec(n2).setOne();

    cout << "======== QR solve ========" << endl;
    auto x0 = LSSolver(A, b).QRSolve();
    cout << x0 << "r(x): " << (b - A * x0).norm2() << endl;
    cout << "======== ColPivot Gauss solve ========" << endl;
    auto x1 = LinearSolver(A, b).LUgaussSolve();
    cout << x1 << "r(x): " << (b - A * x1).norm2() << endl;
    cout << "======== Improved Cholesky solve ========" << endl;
    auto x2 = LinearSolver(A, b).CholeskeyGaussSolve();
    cout << x2 << "r(x): " << (b - A * x2).norm2() << endl;
    cout << endl;
}

void homework3_1()
{
    cout << " ====  HW 3.1 ==== " << endl;
    hw3_1_1();
    hw3_1_2();
    hw3_1_3();
}

void homework3_2()
{
    cout << " ====  HW 3.2 ==== " << endl;
    Vec b({1.00, 0.8125, 0.75, 1.00, 1.3125, 1.75, 2.3125});
    Matrix A(7, 3);
    Vec t({-1, -0.75, -0.5, 0.0, 0.25, 0.5, 0.75});
    for(int i = 0; i < 7; i++)
    {
        A[{i,0}] = t[i]*t[i];
        A[{i, 1}] = t[i];
        A[{i,2}] = 1.0;
    }
    auto x0 = LSSolver(A, b).QRSolve();
    cout << x0 << "r(x): " << (b - A * x0).norm2() << endl << endl;
}

void homework3_3()
{
    cout << " ====  HW 3.3 ==== " << endl;
    Matrix A(
            { {1,4.9176, 1, 3.472, 0.998, 1, 7, 4, 42, 3, 1, 0},
              {1,5.0208, 1, 3.531, 1.5, 2, 7, 4, 62, 1, 1, 0},
              {1,4.5429, 1, 2.275, 1.175, 1, 6, 3, 40,  2, 1, 0},
              {1,4.5573, 1, 4.05, 1.232, 1, 6, 3, 54, 4, 1, 0},
              {1,5.0597, 1, 4.455, 1.121, 1, 6, 3, 42, 3, 1, 0},
              {1,3.891, 1, 4.455, 0.988, 1, 6, 3, 56, 2, 1, 0},
              {1,5.898, 1, 5.85, 1.24, 1, 7, 3, 51, 2, 1,  1},
              {1,5.6039, 1, 9.52, 1.501, 0, 6, 3, 32, 1, 1, 0},
              {1,15.4202, 2.5,  9.8, 3.42, 2, 10, 5, 42, 2, 1, 1},
              {1,14.4598, 2.5, 12.8, 3, 2, 9, 5, 14, 4, 1, 1},
              {1,5.8282, 1, 6.435, 1.225, 2, 6, 3, 32, 1, 1, 0},
              {1,5.3003, 1, 4.9883, 1.552, 1, 6, 3, 30, 1, 2, 0},
              {1,6.2712, 1, 5.52, 0.975, 1, 5, 2, 30, 1, 2, 0},
              {1,5.9592, 1, 6.666, 1.121, 2, 6, 3, 32, 2, 1, 0},
              {1,5.05, 1, 5, 1.02, 0, 5, 2, 46, 4, 1, 1},
              {1,5.6039, 1, 9.52, 1.501, 0, 6, 3, 32, 1, 1, 0},
              {1,8.2464, 1.5, 5.15, 1.664, 2, 8, 4, 50, 4, 1, 0},
              {1,6.6969, 1.5, 6.092, 1.488, 1.5, 7, 3, 22, 1, 1, 1},
              {1,7.7841, 1.5, 7.102, 1.376, 1, 6, 3, 17, 2, 1, 0},
              {1,9.0384, 1, 7.8, 1.5, 1.5, 7, 3, 23, 3, 3, 0},
              {1,5.9894, 1, 5.52, 1.256, 2, 6, 3, 40, 4, 1, 1},
              {1,7.5422, 1.5, 4, 1.69, 1, 6, 3, 22, 1, 1, 0},
              {1,8.7951, 1.5, 9.89, 1.82, 2, 8, 4, 50, 1, 1, 1},
              {1,6.0931, 1.5, 6.7265, 1.652, 1, 6, 3, 44, 4, 1, 0},
              {1,8.3607, 1.5, 9.15, 1.777, 2., 8, 4, 48, 1, 1, 1},
              {1,8.14, 1, 8, 1.504, 2, 7, 3, 3, 1, 3, 0},
              {1,9.1416, 1.5, 7.3262, 1.831, 1.5, 8, 4, 31, 4, 1, 0},
              {1,12, 1.5, 5, 1.2, 2, 6, 3, 30, 3, 1, 1} });

    Vec b({ 25.9, 29.5, 27.9, 25.9, 29.9, 29.9, 30.9,
            28.9, 84.9, 82.9, 35.9, 31.5, 31.0, 30.9,
            30.0, 28.9, 36.9, 41.9, 40.5, 43.9, 37.5,
            37.9, 44.5, 37.9, 38.9, 36.9, 45.8, 41.0 });

    auto x0 = LSSolver(A, b).QRSolve();
    cout << x0 << "r(x): " << (b - A * x0).norm2() << endl;
}

int main()
{
    homework3_1();
    homework3_2();
    homework3_3();
}