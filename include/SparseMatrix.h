//
// Created by 李喆昊 on 2020/11/29.
//

#ifndef CODES_SPARSEMATRIX_H
#define CODES_SPARSEMATRIX_H

#include "commonHeader.h"

namespace ReNLA {

    class CRSMatrix {
    public:
        // Construct a CRS matrix from CSS.
        // **Require rowIdx and colIdx to be sorted!**
        CRSMatrix(int nRow, int nCol, const vector<int>& rowIdx, const vector<int>& colIdx, const vector<long double>& values);
        Matrix toDense() const;
        vector<int> getRowFirstEntryIdx() const;
        vector<int> getColIdx() const;
        vector<long double> getValues() const;

        int rowNum() const;
        int colNum() const;
    private:
        int nRow;
        int nCol;
        vector<int> rowFirstEntryIdx;
        vector<int> colIdx;
        vector<long double> values;
    };
}


#endif //CODES_SPARSEMATRIX_H
