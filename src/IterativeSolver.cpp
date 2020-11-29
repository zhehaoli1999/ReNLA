//
// Created by 李喆昊 on 2020/11/26.
//

#include "../include/IterativeSolver.h"

using namespace ReNLA;

pair<Vec, int> IterativeSolver::commonIterSolve(const Matrix &IterM, const Vec& IterG, const Vec& xInit) {
    int step = 0;
    const int printStepInterval  = 100;
    auto x = xInit;
    auto x0 = x;
    cout << "[Iteration starts]" << endl;
    do {
        step += 1;
        x0 = x;
        x = IterM * x0 + IterG;
        if (step % printStepInterval == 0) {
            cout << "step: " << step << " Delta(x): ";
            cout << (x - x0).normInfin() << endl;
        }
    }while( (x - x0).normInfin() >= 1e-7 );

    return {x, step};
}
pair<Vec, int> IterativeSolver::JacobiIterSolve(const Matrix &A, const Vec &b) {
    auto D = Matrix(A.rowNum()).setDiagValue(A.getDiagValue());
    auto L = - A.getLowTriangle();
    auto U = - A.getUpTriangle();

    auto Dinv = D.lowTriangleInv(); // TODO: optimize this!

    auto B = Dinv * (L+U); // TODO: optimize this!
    auto g = Dinv * b;

    return commonIterSolve(B, g, Vec(b.size()).setNum(0.0));
}

pair<Vec, int> IterativeSolver::GaussSeidelIterSolve(const Matrix &A, const Vec &b) {
    auto D = Matrix(A.rowNum()).setDiagValue(A.getDiagValue());
    auto L = - A.getLowTriangle();
    auto U = - A.getUpTriangle();

    auto L1 = (D-L).lowTriangleInv() * U;
    auto g = (D-L).lowTriangleInv() * b;

    return commonIterSolve(L1, g, Vec(b.size()).setNum(0.0));
}

pair<Vec, int> IterativeSolver::SORIterSolve(const Matrix &A, const Vec &b, double w) {
    auto D = Matrix(A.rowNum()).setDiagValue(A.getDiagValue());
    auto L = - A.getLowTriangle();
    auto U = - A.getUpTriangle();

    auto Lw = (D - w * L).lowTriangleInv() * ((1- w)*D + w*U);
    auto g = w * (D - w*L).lowTriangleInv() * b;

    return commonIterSolve(Lw, g, Vec(b.size()).setNum(0.0));
}


