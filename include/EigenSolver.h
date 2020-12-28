//
// Created by 李喆昊 on 2020/12/27.
//

#ifndef EIGENSOLVER_H
#define EIGENSOLVER_H
#include "commonHeader.h"
#include "LSSolver.h"

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

        static pair<long double, Vec> ImplicitQR(Matrix A);

        //@brief: do upHessenberg to A: H = Q^T A Q
        //@return: pair{H, Q}
        static pair<Matrix, Matrix> upHessenberg(Matrix A);

    };
}
#endif //EIGENSOLVER_H
