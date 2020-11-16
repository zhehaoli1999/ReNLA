//
// Created by 李喆昊 on 2020/11/12.
//

#ifndef CODES_LSSOLVER_H
#define CODES_LSSOLVER_H

#include "Matrix.h"
#include "Vec.h"
#include "LinearSolver.h"

namespace ReNLA
{
    class LSSolver{
    public:
        LSSolver(const Matrix& A, const Vec& b);
        static Vec householder(Vec x); // \beta can be stored at returned Vec[0]
        static pair<Matrix, Vec> QRdecomposition(Matrix A);
        Vec QRSolve();
    private:
        Matrix A;
        Vec b;
    };
}
#endif //CODES_LSSOLVER_H
