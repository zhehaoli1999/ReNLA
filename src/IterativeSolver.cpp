//
// Created by 李喆昊 on 2020/11/26.
//

#include "../include/IterativeSolver.h"

using namespace ReNLA;

Vec IterativeSolver::JacobiIterSolve(const Matrix &A, const Vec &b) {
    auto D = Matrix(A.getDiagValue());
    auto L = A.getLowTriangle();
    auto U = A.getUpTriangle();

}

