#include <iostream>
#include <vector>
#include "Matrix.h"
#include "Vec.h"
using namespace std;
using namespace NLA;

void MatrixTest()
{
    Matrix a = Matrix(3,3).setIdentity();
    Matrix b = Matrix(3, 3).setTripleDiag(1,2,3);
    cout << "======== a,b ========"<< endl;
    cout << a;
    cout << b;
    cout << b[{1,2}] << b[2][1] << endl;
    cout << b[{1,0}]<< endl;
    cout << "======== b * b ========"<< endl;
    cout << b * b;
    cout << "======== b + b ========"<< endl;
    cout << b + b;
    cout << "=======b + 100========"<< endl;
    cout << b + 100.0;
    cout << "=======b * 100========"<< endl;
    cout << b * 100.0;
    cout << "======= construct ========"<< endl;
    Matrix g({{1,2,3},{1,2,3}});
    cout << g;
}

void VecTest()
{
    Vec x({1,2,3});
    cout << x[{0,1}];
    x.setSlice(1,2, x[{0,1}]);
    cout << x;
}
int main() {
    //MatrixTest();
    VecTest();
    return 0;
}
