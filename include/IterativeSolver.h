//
// Created by 李喆昊 on 2020/11/26.
//

#ifndef CODES_ITERATIVESOLVER_H
#define CODES_ITERATIVESOLVER_H
#include "commonHeader.h"
#include "constValues.h"

namespace ReNLA{
    class IterativeSolver
    {
        static Vec JacobiIterSolve(const Matrix& A, const Vec& b);

        static Vec GaussSeidelIterSolve(const Matrix& A, const Vec& b);

        static Vec SORIterSolve(const Matrix& A, const Vec& b);
    };
}


#endif //CODES_ITERATIVESOLVER_H
