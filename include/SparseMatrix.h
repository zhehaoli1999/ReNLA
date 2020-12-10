//
// Created by 李喆昊 on 2020/11/29.
//

#ifndef CODES_SPARSEMATRIX_H
#define CODES_SPARSEMATRIX_H

#include "commonHeader.h"

namespace ReNLA {

    class CSRMatrix : Matrix{
    public:
        // Construct a CRS matrix from CSS.
        // **Require rowIdx to be sorted!**
        CSRMatrix(int nRow, int nCol, const vector<int>& rowIdx, const vector<int>& colIdx, const vector<long double>& values);
        Matrix toDense() const;
        vector<int> getRowFirstEntryIdx() const;
        vector<int> getColIdx() const;
        vector<long double> getValues() const;

        long double &operator[](const pair<int, int>);
        long double operator[](const pair<int, int>) const;

        friend Vec operator*(const CSRMatrix &a, const Vec &v);

        int rowNum() const override;
        int colNum() const override;
    private:
        int nRow;
        int nCol;
        vector<int> rowFirstEntryIdx;
        vector<int> colIdx;
        vector<long double> values;
    };
}


#endif //CODES_SPARSEMATRIX_H
