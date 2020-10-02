//
// Created by 李喆昊 on 2020/9/29.
//
#ifndef CODES_MATRIX_H
#define CODES_MATRIX_H
#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

namespace NLA {
    class Matrix {
    public:
        Matrix(vector<vector<float>>);
        Matrix(vector<float>);
        Matrix(int nRow, int nCol, float num);
        Matrix(int nRow, int nCol); // Create a zero matrix
        Matrix(int nRow);

        Matrix setNum(float num);
        Matrix setIdentity();
        Matrix setZero();
        Matrix setTripleDiag(float lambda, float lambdaUp, float lambdaDown);

        vector<float>& operator[](const int idx);

        Matrix operator+(Matrix &);
        Matrix operator+=(Matrix &);
        Matrix operator+(float);
        Matrix operator+=(float);

        Matrix operator-(Matrix &);
        Matrix operator-(float);

        Matrix operator*(float);
        Matrix operator*=(float);

        // Matrix multiplication
        Matrix operator*(Matrix& b);
        Matrix elementwiseMul(Matrix &b);
        friend ostream& operator<<(ostream& os, Matrix a);

    protected:
        vector<vector<float>> data;
        int nRow, nCol;
    };

}
#endif //CODES_MATRIX_H
