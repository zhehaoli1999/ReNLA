//
// Created by 李喆昊 on 2020/11/26.
//

#ifndef CODES_ITERATIVESOLVER_H
#define CODES_ITERATIVESOLVER_H
#include "commonHeader.h"
#include "constValues.h"
#include "SparseMatrix.h"

namespace ReNLA{
    class IterativeSolver
    {
    public:
        static pair<Vec, int> JacobiIterSolve(const Matrix& A, const Vec& b);

        static pair<Vec, int> GaussSeidelIterSolve(const Matrix& A, const Vec& b);

        static pair<Vec, int> SORIterSolve(const Matrix& A, const Vec& b, double w=1.17);

        static pair<Vec, int> commonIterSolve(const Matrix& IterM,  const Vec& IterG, const Vec& xInit);

        static pair<Vec, int> sparseJacobiIterSolve(const CRSMatrix& A, const Vec& b);

        static pair<Vec, int> sparseGSIterSolve(const CRSMatrix& A, const Vec& b);

        static pair<Vec, int> sparseSORIterSolve(const CRSMatrix& A, const Vec& b);

    };
}


#endif //CODES_ITERATIVESOLVER_H
