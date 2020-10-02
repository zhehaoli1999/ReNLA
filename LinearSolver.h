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
        LinearSolver(Matrix& A, Vec&b);

        static Matrix LUdecompose(Matrix& m);
        static Matrix LUdecomposeColPivot(Matrix& m, Matrix& P);

        Vec lowTriangleSolve();
        Vec upTriangleSolve();

        Vec gaussSolve(bool isColPivot = true);


    private:
        Matrix A;
        Vec b;
    };
}


#endif //CODES_LINEARSOLVER_H
