//
// Created by 李喆昊 on 2020/11/29.
//

#include "../include/SparseMatrix.h"

using namespace ReNLA;

CRSMatrix::CRSMatrix(int nRow, int nCol, const vector<int> &rowIdx, const vector<int> &colIdx, const vector<long double> &values) {
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

int CRSMatrix::rowNum() const {
    return this->nRow;
}

int CRSMatrix::colNum() const {
    return this->nCol;
}

vector<long double> CRSMatrix::getValues() const{
    return this->values;
}

vector<int> CRSMatrix::getColIdx() const{
    return this->colIdx;
}

vector<int> CRSMatrix::getRowFirstEntryIdx() const{
    return this->rowFirstEntryIdx;
}

Matrix CRSMatrix::toDense() const
{
    auto M = Matrix(nRow, nCol);

    int row = 0;
    for(auto it= this->rowFirstEntryIdx.begin(); it!=this->rowFirstEntryIdx.end(); it++)
    {
        //TODO: Require that no row is a zero row
        for(int j = *it; j < *(it+1); j++)
        {
            int colIndex = this->colIdx[j];
            M[{row, colIndex}] = this->values[j];
        }
        row ++;
    }
    return M;
}