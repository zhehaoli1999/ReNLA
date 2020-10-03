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
        static Matrix LUdecomposeColPivot(Matrix& m, vector<pair<int, int>>& P);
        static Matrix CholeskyDecompose(Matrix& m, bool isImproved = true);

        Vec lowTriangleSolve(bool isDiagAllOne = false);
        Vec upTriangleSolve();

        Vec LUgaussSolve(bool isColPivot = true);
        Vec CholeskeyGaussSolve(bool isImproved = true);

    private:
        Matrix A;
        Vec b;
    };
}


#endif //CODES_LINEARSOLVER_H
