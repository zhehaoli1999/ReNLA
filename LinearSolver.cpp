//
// Created by 李喆昊 on 2020/10/2.
//

#include "LinearSolver.h"

using namespace NLA;

LinearSolver::LinearSolver(Matrix &A, Vec &x, Vec &b) : A{A},x{x}, b{b}
{}

Vec & LinearSolver::diagSolve() {

}
Vec & LinearSolver::basicGaussSolve() {

}