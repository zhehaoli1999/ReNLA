//
// Created by 李喆昊 on 2020/11/26.
//

#include "../include/IterativeSolver.h"
#include "../include/Timer.h"

using namespace ReNLA;

pair<Vec, int> IterativeSolver::commonIterSolve(const Matrix &IterM, const Vec& IterG, const Vec& xInit) {
    int step = 0;
    const int printStepInterval  = 1000;
    auto x = xInit;
    auto x0 = x;
    cout << "[Iteration starts]" << endl;
    do {
        step += 1;
        x0 = x;
        x = IterM * x0 + IterG;
//        if (step % printStepInterval == 0) {
//            cout << "step: " << step << " Delta(x): ";
//            cout << (x - x0).normInfin() << endl;
//        }
    }while( (x - x0).normInfin() >= 1e-7 );

    return {x, step};
}
pair<Vec, int> IterativeSolver::JacobiIterSolve(const Matrix &A, const Vec &b) {
    assert(A.rowNum() == A.colNum()); // Require A to be square matrix

    auto D = A.getDiagValue();
    auto L = - A.getLowTriangle();
    auto U = - A.getUpTriangle();

//    auto Dinv = D.lowTriangleInv(); // TODO: optimize this!
//    auto B = Dinv * (L+U);
//    auto g = Dinv * b;
    auto B = L + U;
    auto g = b;
    for(int i = 0; i < A.rowNum(); i++)
    {
        assert(D[i] != 0.0);
        for(int j = 0; j < A.rowNum(); j++)
            B[{i,j}] *= 1.0 / D[i];
        g[i] *= 1.0 / D[i];
    }

    return commonIterSolve(B, g, Vec(b.size()).setNum(0.0));
}

pair<Vec, int> IterativeSolver::GaussSeidelIterSolve(const Matrix &A, const Vec &b) {
    return SORIterSolve(A, b, 1.0);
}

pair<Vec, int> IterativeSolver::SORIterSolve(const Matrix &A, const Vec &b, double w) {
    auto D = Matrix(A.rowNum()).setDiagValue(A.getDiagValue());
    auto L = - A.getLowTriangle();
    auto U = - A.getUpTriangle();

    auto inv =  (D - w * L).lowTriangleInv();
    auto Lw = inv * ((1- w)*D + w*U);
    auto g = w * inv * b;

    return commonIterSolve(Lw, g, Vec(b.size()).setNum(0.0));
}

pair<Vec, int> IterativeSolver::CGIterSolve(const Matrix &A, const Vec &b) {
    /* Conjugate Gradient iteration method
     *
     *  1. x_{k+1} = x_k + \alpha_k * p_k
     *     \alpha_k = < r_k, r_k > / ( p_k^T A p_k )
     *  2. r_{k+1} = b - A * x_{k+1}
     *             = r_k - \alpha * A * p_k
     *  3. p_{k+1} = r_{k+1} + \beta_k * p_k
     *      \beta_k = - < r_{k+1}, r_{k+1} > / <r_k, r_k>
     */
    auto x = Vec(b.size());
    int step = 0;
    auto r = b - A * x;
    auto rho = r.dot(r);
    auto rho_hat = rho;
    auto p = r; // p0 = r0

    auto epsi  = 1e-15 * b.norm2();
    int stepMax = 1e6;
    while(rho > epsi * epsi && step < stepMax)
    {
        step += 1;
        if(step > 1)
        {
            auto beta = rho / rho_hat; // \beta_k = - < r_{k+1}, r_{k+1} > / <r_k, r_k>
            p = r + beta * p;          // p_{k+1} = r_{k+1} + \beta_k * p_k
        }
        auto w = A*p;
        auto alpha = rho / p.dot(w); // \alpha_k = < r_k, r_k > / ( p_k^T A p_k )
        x = x + alpha * p;           //  x_{k+1} = x_k + \alpha_k * p_k
        r = r - alpha * w;           //  r_{k+1} = r_k - \alpha * A * p_k
        rho_hat = rho;
        rho = r.dot(r);
    }
    return {x, step};
}

pair<Vec, int> IterativeSolver::sparseJacobiIterSolve(const CSRMatrix &A, const Vec &b) {
    int n = b.size();
    assert(A.colNum() == A.rowNum() && A.rowNum() == n);

    int step = 0;
    const int printStepInterval  = 1000;

    auto x = Vec(n); // initial vector is all zeros
    auto x0 = x;
    cout << "[Iteration starts]" << endl;
    do {
        step += 1;
        x0 = x;

        auto rowFirstEntryIdx = A.getRowFirstEntryIdx();
        auto colIdx = A.getColIdx();
        auto values = A.getValues();

        ///////// Jacobi iteration
        auto it = rowFirstEntryIdx.begin();
        for(int i =0; i < n; i++, it++)
        {
            long double sigma = 0;
            long double aii = 0;
            for(int j = *it; j < *(it+1); j++)
            {
                int colIndex = colIdx[j];
                long double a = values[j];
                if(colIndex != i)
                    sigma += a * x0[colIndex];
                else {
                    aii = a;
                    assert(aii != 0.0);
                }
            }
            x[i] = 1 / aii * ( b[i] - sigma);
        }
        //////////////

//        if (step % printStepInterval == 0) {
//            cout << "step: " << step << " Delta(x): ";
//            cout << (x - x0).normInfin() << endl;
//        }
    }while( (x - x0).normInfin() >= 1e-7 );

    return {x, step};
}

pair<Vec, int> IterativeSolver::sparseGSIterSolve(const CSRMatrix &A, const Vec &b) {
    return sparseSORIterSolve(A, b, 1.0);
}

pair<Vec, int> IterativeSolver::sparseSORIterSolve(const CSRMatrix &A, const Vec &b, double w) {
    int n = b.size();
    assert(A.colNum() == A.rowNum() && A.rowNum() == n);

    int step = 0;
    const int printStepInterval  = 1000;

    auto x = Vec(n);
    auto x0 = x;
    cout << "[Iteration starts]" << endl;
    do {
        step += 1;
        x0 = x;

        auto rowFirstEntryIdx = A.getRowFirstEntryIdx();
        auto colIdx = A.getColIdx();
        auto values = A.getValues();

        ///////// SOR iteration
        auto it = rowFirstEntryIdx.begin();
        for(int i =0; i < n; i++, it++)
        {
            long double sigma = 0;
            long double aii = 0;
            for(int j = *it; j < *(it+1); j++)
            {
                int colIndex = colIdx[j];
                long double a = values[j];
                if(colIndex != i)
                    sigma += a * x[colIndex]; // Here different with Jacobi
                else {
                    aii = a;
                    assert(aii != 0.0);
                }
            }
            x[i] = x[i] + w*(1 / aii * ( b[i] - sigma) - x[i]);
        }
        //////////////

//        if (step % printStepInterval == 0) {
//            cout << "step: " << step << " Delta(x): ";
//            cout << (x - x0).normInfin() << endl;
//        }
    }while( (x - x0).normInfin() >= 1e-7 );

    return {x, step};
}

pair<Vec, int> IterativeSolver::sparseCGIterSolve(const CSRMatrix &A, const Vec &b) {
    /* Conjugate Gradient iteration method
     *
     *  1. x_{k+1} = x_k + \alpha_k * p_k
     *     \alpha_k = < r_k, r_k > / ( p_k^T A p_k )
     *  2. r_{k+1} = b - A * x_{k+1}
     *             = r_k - \alpha * A * p_k
     *  3. p_{k+1} = r_{k+1} + \beta_k * p_k
     *      \beta_k = - < r_{k+1}, r_{k+1} > / <r_k, r_k>
     */

    auto x = Vec(b.size());
    int step = 0;
    auto r = b - A * x;
    auto rho = r.dot(r);
    auto rho_hat = rho;
    auto p = r; // p0 = r0

    auto epsi  = 1e-8 * b.norm2();
    int stepMax = 1e6;
    while(rho > epsi * epsi && step < stepMax)
    {
        step += 1;
        if(step > 1)
        {
            auto beta = rho / rho_hat; // \beta_k = - < r_{k+1}, r_{k+1} > / <r_k, r_k>
            p = r + beta * p;          // p_{k+1} = r_{k+1} + \beta_k * p_k
        }
        auto w = A*p;
        auto alpha = rho / p.dot(w); // \alpha_k = < r_k, r_k > / ( p_k^T A p_k )
        x = x + alpha * p;           //  x_{k+1} = x_k + \alpha_k * p_k
        r = r - alpha * w;           //  r_{k+1} = r_k - \alpha * A * p_k
        rho_hat = rho;
        rho = r.dot(r);
    }
    return {x, step};
}

