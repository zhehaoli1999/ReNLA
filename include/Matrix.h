//
// Created by 李喆昊 on 2020/9/29.
//
#ifndef CODES_MATRIX_H
#define CODES_MATRIX_H
#include <iostream>
#include <vector>
#include <cassert>
#include "Vec.h"
using namespace std;

namespace ReNLA {
    class Matrix {
    public:
        Matrix(vector<vector<double>> v, bool isColPrior=false);
        Matrix(vector<Vec>);
        Matrix(vector<double>);
        Matrix(int nRow, int nCol, double num);
        Matrix(int nRow, int nCol); // Create a zero matrix
        Matrix(int nRow);

        vector<int> shape() const;

        Matrix transpose() const;

        Matrix setNum(double num);
        Matrix setIdentity();
        Matrix setZero();
        Matrix setTripleDiag(double lambda, double lambdaUp, double lambdaDown);
        Matrix setHilbert();

        // get entry of Matrix[col][row]
        Vec& operator[](const int idx) const;

        // get entry of Matrix[{row, col}]
        double& operator[](const pair<int, int>) const;

        // slice row vector
        Vec operator[](const pair<int, pair<int, int>>) const;
        // slice col vector
        Vec operator[](const pair<pair<int, int>, int>) const;

        // slice sub matrix
        Matrix operator[](const pair<pair<int, int>, pair<int, int>>) const;

        Matrix setSlice(const pair<pair<int, int>, pair<int, int>>, Matrix&);
        Matrix getSlice(const pair<pair<int, int>, pair<int, int>>) const;

        friend bool operator== (const Matrix& a, const Matrix& b);

        friend Matrix operator+(const Matrix& a, const Matrix& b);
        friend Matrix operator+(const Matrix& a, const double b);
        friend Matrix operator+(const double b, const Matrix& a);

        friend Matrix operator-(const Matrix& a, const Matrix& b);
        friend Matrix operator-(const Matrix& a, const double b);

        friend Matrix operator*(const Matrix& a, const double b);
        friend Matrix operator*(const double b, const Matrix& a);

        friend Matrix matMul(const Matrix& a, const Matrix& b);

        friend Matrix operator/(const Matrix& a, const double b);

        Matrix operator-() const;
        Matrix& operator+=(const Matrix &);
        Matrix& operator+=(const double);

        Matrix& operator-=(Matrix &);
        Matrix operator-(double);

        Matrix operator*(double);
        Matrix operator*=(double);

        // Matrix multiplication
        Matrix operator*(Matrix& b);
        Vec operator*(Vec b);
        Matrix elementwiseMul(Matrix &b);
        friend ostream& operator<<(ostream& os, Matrix a);

        Matrix swapRow(int idx1, int idx2);

    protected:
        vector<Vec> colVecArray;
        int nRow, nCol;
    };

}
#endif //CODES_MATRIX_H
