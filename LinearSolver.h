//
// Created by 李喆昊 on 2020/10/2.
//

#ifndef CODES_LINEARSOLVER_H
#define CODES_LINEARSOLVER_H

#include "Matrix.h"
#include "Vec.h"

namespace NLA {
    class LinearSolver {
    public:
        LinearSolver(Matrix& A, Vec& x, Vec&b);

        Vec& diagSolve();

        Vec& basicGaussSolve();
        Vec& colPivotSolve();

    private:
        Matrix A;
        Vec x;
        Vec b;
    };
}


#endif //CODES_LINEARSOLVER_H
