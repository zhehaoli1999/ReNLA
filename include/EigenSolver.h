//
// Created by 李喆昊 on 2020/12/27.
//

#ifndef EIGENSOLVER_H
#define EIGENSOLVER_H
#include "commonHeader.h"
#include "LSSolver.h"
#include <complex>

namespace ReNLA {
    class EigenSolver {
    public:

        //@brief: power alg
        //@return: pair:{ eigenValue, eigenVec (normalized) }
        static pair<long double, Vec> powerAlg(const Matrix A);

        //@brief: get friend matrix
        //@param: efficients: {a0, a1, ... an-1}
        //@return: Matrix
        static Matrix getFriendMatrixFromPolynomial(const Vec efficients);

        //@brief: Do implicit QR on A (Real Schur Decomposition): Q^T A Q = U
        //@return: pair{U, Q} where Q^T A Q = U
        static pair<Matrix, Matrix> ImplicitQRDecomposition(Matrix A);

        //@brief: do upHessenberg to A: H = Q^T A Q
        //@return: pair{H, Q}
        static pair<Matrix, Matrix> upHessenberg(Matrix A);

        //@brief: subroutine of ImplicitQR. Do double-step offset to upHessenberg matrix.
        //@return: pair{H_offseted, P}, to make H_offseted = P^T H P
        static pair<Matrix, Matrix> FrancisQRIter(Matrix H);

        //@brief: subroutine of ImplicitQR
        //@return: pair{U, Q} where Q^T A Q = U
        static bool ImplicitQRConvergenceCheck(Matrix& H, Matrix& Q);

        //@brief: get all eigen values
        //@param: A to be decomposed
        //@return: vector of diagonal matrix in U where Q^T A Q = U from Schur Decomposition
        static vector<Matrix> getEigenMatrices(Matrix A);

        static vector<complex<double>> getEigenValues(Matrix A, bool print_result= true);

    };
}
#endif //EIGENSOLVER_H
