//
// Created by 李喆昊 on 2020/10/2.
//

#include "Vec.h"
using namespace NLA;

Vec::Vec(vector<float>v) : data{v}
{}

float& Vec::operator[](const int idx) {
    return this->data[idx];
}

ostream& NLA::operator<<(ostream& os, Vec x)
{
    os << "[";
    for(int i = 0; i < x.data.size(); i++)
    {
       cout <<" " << x[i];
        if(i < x.data.size() -1) cout << ",";
    }
   cout << " ]^T" << endl;
    return os;
}
