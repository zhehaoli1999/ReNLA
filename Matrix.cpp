//
// Created by 李喆昊 on 2020/9/29.
//
#include "Matrix.h"

using namespace NLA;

Matrix::Matrix(vector<Vec> v) : colVecArray(v)
{
    assert(v.size() > 0);
    nCol = v.size();
    nRow = v[0].size();
}

Matrix::Matrix(vector<vector<float> > v, bool isColPrior)
{
    assert(v.size() > 0);
    assert(v[0].size() > 0);
    if(isColPrior) {
        nCol = v.size();
        nRow = v[0].size();
        for (int i = 0; i < nCol; i++) {
            colVecArray.emplace_back(v[i]);
        }
    }
    else{
        nRow = v.size();
        nCol = v[0].size();
        for(int i = 0; i < nCol; i++)
        {
            vector<float> colVec;
            for(int j = 0; j < nRow; j++)
            {
                colVec.push_back(v[j][i]);
            }
            colVecArray.emplace_back(colVec);
        }
    }
}

Matrix::Matrix(vector<float> v)
{
    assert(v.size() > 0);
    colVecArray.emplace_back(v);
    nCol = 1;
    nRow = v.size();
}

Matrix::Matrix(int nRow, int nCol, float num)
{
    assert(nRow > 0);
    assert(nCol > 0);
    vector<Vec> mat;
    for(int i = 0; i < nCol; i++)
    {
        mat.emplace_back(vector<float>(nRow, num));
    }
    colVecArray = mat;
    this->nRow = nRow;
    this->nCol = nCol;
}

Matrix::Matrix(int nRow, int nCol) : Matrix::Matrix{nRow, nCol, 0.0}
{}

Matrix::Matrix(int nRow) : Matrix::Matrix{nRow, nRow}
{}

vector<int> Matrix::shape() {
    return {nRow, nCol};
}

Matrix Matrix::transpose() {
    vector<vector<float>> mat(nCol);
    for(int i = 0; i < nRow; i++)
    {
        for(int j = 0; j < nCol; j++)
        {
            mat[j].push_back((*this)[{i,j}]);
        }
    }
    return Matrix(mat);
}

Matrix Matrix::setNum(float num)
{
    for(int i = 0; i < nRow; i++)
    {
        for(int j = 0; j < nCol; j++)
           // or (*this)[{i,j}] = num;
           colVecArray[j][i] = num;
    }
    return (*this);
}
Matrix Matrix::setZero()
{
    return this->setNum(0.0);
}

Matrix Matrix::setIdentity() {
    // Not require square
    this->setZero();
    for(int i = 0; i < nRow; i++)
    {
         this->colVecArray[i][i] = 1.0;
    }
    return (*this);
}

Vec& Matrix::operator[](const int idx) {
    return colVecArray[idx];
}

float& Matrix::operator[](const pair<int, int> idx)
{
    assert(idx.second >= 0 && idx.second < nCol && idx.first >= 0 && idx.first < nRow);
    return colVecArray[idx.second][idx.first];
}

Matrix Matrix::operator*(Matrix &b) {
    assert(this->nCol == b.nRow);
    Matrix m = Matrix(this->nRow, b.nCol).setZero();

    for (int i = 0; i < m.nRow; i++) {
        for (int j = 0; j < m.nCol; j++) {
            for (int k = 0; k < this->nCol; k++) {
                m[{i,j}] += (*this)[{i,k}] * b[{k,j}];
            }
        }
    }
    return m;
}

Matrix Matrix::operator*(float a) {
    Matrix m = Matrix(this->nRow, this->nCol).setZero();
    for(int i = 0; i < m.nRow; i++)
    {
        for(int j = 0; j < m.nCol; j++)
        {
            m[{i,j}] = (*this)[{i,j}] * a;
        }
    }
    return m;
}

Matrix Matrix::operator+(float a) {
    Matrix m = Matrix(this->nRow, this->nCol).setZero();
    for(int i = 0; i < m.nRow; i++)
    {
        for(int j = 0; j < m.nCol; j++)
        {
            m[{i,j}] = (*this)[{i,j}] + a;
        }
    }
    return m;
}

Matrix Matrix::operator*=(float a)
{
    for(int i = 0; i < this->nRow; i ++)
    {
        for(int j = 0; j < this->nCol; j++)
        {
            (*this)[{i,j}] *= a;
        }
    }
    return (*this);
}

Matrix Matrix::setTripleDiag(float lambda, float lambdaUp, float lambdaDown)
{
    assert(this->nRow == this->nCol);
    this->setZero();
    for(int i = 0; i < nRow; i++)
    {
        (*this)[{i,i}] = lambda;
        if(i >= 1)
            (*this)[{i,i-1}] = lambdaDown;
        if(i <= nRow-2)
            (*this)[{i,i+1}] = lambdaUp;
    }
    return (*this);
}

Matrix Matrix::operator+(Matrix &b)
{
    assert(this->nRow == b.nRow);
    assert(this->nCol == b.nCol);
    Matrix m = Matrix(this->nRow, this->nCol).setZero();
    for(int i = 0; i < this->nRow; i ++)
    {
        for(int j = 0; j < this->nCol; j++)
        {
            m[{i,j}] = (*this)[{i,j}] + b[{i,j}];
        }
    }
    return m;
}

ostream& NLA::operator<<(ostream &os, Matrix a) {
    os << "[";
    for(int i = 0; i < a.nRow; i++)
    {
        os << "[ ";
        for(int j = 0; j < a.nCol; j++)
        {
            os << a[{i,j}];
            if(j < a.nCol - 1 ) os << ", ";
        }
        os << " ]";
        if(i < a.nRow -1 ) os <<"," << endl << " ";
    }
    os << "]" << endl;
    return os;
}





