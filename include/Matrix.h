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
        Matrix(vector<vector<long double>> v, bool isColPrior=false);
        Matrix(vector<Vec>);
        Matrix(const Vec&);
        Matrix(vector<long double>);
        Matrix(int nRow, int nCol, long double num);
        Matrix(int nRow, int nCol); // Create a zero matrix
        Matrix(int nRow);

        vector<int> shape() const;

        Matrix transpose() const;

        Matrix setNum(long double num);
        Matrix setIdentity();
        Matrix setZero();
        Matrix setTripleDiag(long double lambda, long double lambdaUp, long double lambdaDown);
        Matrix setHilbert();

        // get entry of Matrix[col][row]
        Vec& operator[](const int idx);
        Vec operator[](const int idx) const;

        // get entry of Matrix[{row, col}]
        long double& operator[](const pair<int, int>);
        long double operator[](const pair<int, int>) const;

        // slice row vector
        Vec operator[](const pair<int, pair<int, int>>) const;
        // slice col vector
        Vec operator[](const pair<pair<int, int>, int>) const;

        // slice sub matrix
        Matrix operator[](const pair<pair<int, int>, pair<int, int>>) const;

        Matrix setSlice(const pair<pair<int, int>, pair<int, int>>, const Matrix&);
        Matrix getSlice(const pair<pair<int, int>, pair<int, int>>) const;

        friend ostream& operator<<(ostream& os, const Matrix a);
        friend bool operator== (const Matrix& a, const Matrix& b);

        friend Matrix operator+(const Matrix& a, const Matrix& b);
        friend Matrix operator+(const Matrix& a, const long double b);
        friend Matrix operator+(const long double b, const Matrix& a);

        friend Matrix operator-(const Matrix& a, const Matrix& b);
        friend Matrix operator-(const Matrix& a, const long double b);

        friend Matrix operator* (const Matrix& a, const Matrix& b);
        friend Matrix matMul(const Matrix& a, const Matrix& b);

        friend Vec operator* (const Matrix& a, const Vec& v);
        //TODO:  friend Vec operator* (const Vec& v, const Matrix& a);
        friend Matrix operator*(const Matrix& a, const long double b);
        friend Matrix operator*(const long double b, const Matrix& a);

        friend Matrix operator/(const Matrix& a, const long double b);

        Matrix operator-() const;
        Matrix& operator+=(const Matrix &);
        Matrix& operator+=(const long double);

        Matrix& operator-=(const Matrix &);
        Matrix& operator-=(const long double);

        // Matrix multiplication
        Matrix& operator*=(const Matrix& b);
        Matrix& operator*=(const long double);
        //TODO: Vec operator*=(const Vec& b);

        Matrix& operator/= (const long double);

        Matrix& elementwiseMul(Matrix &b);

        Matrix swapRow(int idx1, int idx2);

        long double normInfin() const;
        long double norm1() const;
        long double norm2() const;

    protected:
        vector<Vec> colVecArray;
        int nRow, nCol;
    };
}
#endif //CODES_MATRIX_H
