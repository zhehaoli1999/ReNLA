//
// Created by 李喆昊 on 2021/1/4.
//

#ifndef SYMMETRICEIGENSOLVER_H
#define SYMMETRICEIGENSOLVER_H

#include "../include/commonHeader.h"
#include "../include/EigenSolver.h"

namespace ReNLA
{
    class SymmetricEigenSolver : public EigenSolver
    {
    public:
        static pair<Matrix, Matrix> tripleDiagonalDecomposition(Matrix A);

        //@brief: do implicit symmetric QR iteration with Wilkinson offset
        //@return: pair{T', G}, to make T' = Q^T T Q
        static pair<Matrix, Matrix> WilkinsonImplicitQRIter(Matrix A);

        static pair<Matrix, Matrix> ImplicitQRDecomposition(Matrix A);

        //@brief: Do threshold Jacobi method on symmetric matrix A to get eigen values.
        //@return: pair{A', Q}, to make AQ = QA'
        static pair<Matrix, Matrix> thresholdJacobi(Matrix A, bool print_iter_result=true);

        //@brief: Binary search the No.${index} eigen value of matrix A, note that A should be a triangularDiag Matrix
        //@return: the No.${index} eigen value of A
        static long double binarySearch(const Matrix& A, const int index);
    };
}


#endif //SYMMETRICEIGENSOLVER_H
