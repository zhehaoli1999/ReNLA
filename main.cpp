#include <iostream>
#include <vector>
#include "Matrix.h"
#include "Vec.h"
#include <valarray>
using namespace std;
using namespace NLA;

void MatrixTest()
{
    Matrix a = Matrix(3,3).setIdentity();
    Matrix b = Matrix(3, 3).setTripleDiag(1,2,3);
    cout << "======== a ========"<< endl;
    cout << a;
    cout << a[1][2];
    cout << a[1][1];
    cout << "======== b * b ========"<< endl;
    cout << b;
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
   // Vec x({1,2,3});
   // cout << x;
}
int main() {
    //MatrixTest();
    VecTest();
    return 0;
}
