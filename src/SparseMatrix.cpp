//
// Created by 李喆昊 on 2020/11/29.
//

#include "../include/SparseMatrix.h"

using namespace ReNLA;

CSRMatrix::CSRMatrix(int nRow, int nCol, const vector<int> &rowIdx, const vector<int> &colIdx, const vector<long double> &values) {
    this->nRow = nRow;
    this->nCol = nCol;

    int n = rowIdx.size();
    assert(n == colIdx.size() && n == values.size());

    this->colIdx = colIdx;
    this->values = values;

    // construct rowFirstEntryIdx
    this->rowFirstEntryIdx.push_back(0);
    int startRowIdx = rowIdx[0];
    for(int i =1 ; i < n; i++)
    {
        if(rowIdx[i] != startRowIdx)
        {
            this->rowFirstEntryIdx.push_back(i);
            startRowIdx = rowIdx[i];
        }
    }
    this->rowFirstEntryIdx.push_back(n);
}

int CSRMatrix::rowNum() const {
    return this->nRow;
}

int CSRMatrix::colNum() const {
    return this->nCol;
}

vector<long double> CSRMatrix::getValues() const{
    return this->values;
}

vector<int> CSRMatrix::getColIdx() const{
    return this->colIdx;
}

vector<int> CSRMatrix::getRowFirstEntryIdx() const{
    return this->rowFirstEntryIdx;
}

Matrix CSRMatrix::toDense() const
{
    auto M = Matrix(nRow, nCol);

    int row = 0;
    for(auto it= this->rowFirstEntryIdx.begin(); it!=this->rowFirstEntryIdx.end()-1; it++)
    {
        //TODO: Require no row is a zero row!
        for(int j = *it; j < *(it+1); j++)
        {
            int colIndex = this->colIdx[j];
            M[{row, colIndex}] = this->values[j];
        }
        row ++;
    }
    return M;
}

Vec ReNLA::operator*(const CSRMatrix& A, const Vec& v)
{
    assert(A.colNum() == v.size());
    auto result = Vec(v.size());

    //TODO: Require no row is a zero row!
    int row = 0;
    auto rowFirstEntryIdx = A.getRowFirstEntryIdx();
    auto Avalues = A.getValues();
    auto colIdx = A.getColIdx();

    for(auto it= rowFirstEntryIdx.begin(); it!= rowFirstEntryIdx.end()-1; it++)
    {
        long double sum = 0.0;
        for(int j = *it; j < *(it+1); j++)
        {
            int colIndex = colIdx[j];
            long double val = Avalues[j];
            sum += val * v[colIndex];
        }
        if(row < result.size()) {
            result[row] = sum;
        }
        row ++;
    }
    return result;
}