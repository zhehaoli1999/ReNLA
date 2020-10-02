//
// Created by 李喆昊 on 2020/10/2.
//

#include "Vec.h"
#include <cmath>
using namespace NLA;

Vec::Vec(vector<float>v) : data{v}
{}

Vec::Vec(int n)
{
    data = vector<float>(n, 0.0);
}

int Vec::size()
{
    return data.size();
}
float& Vec::operator[](const int idx) {
    return this->data[idx];
}

Vec Vec::operator[](const pair<int, int> slice)
{
    assert(slice.second >= slice.first && slice.second <= this->data.size() - 1);
    return Vec(vector(this->data.begin()+slice.first,
                        this->data.begin()+slice.second + 1));
}

Vec Vec::setSlice(int begin, int end, Vec v)
{
    assert(v.data.size() == end - begin + 1);
    for(int i = begin; i <= end; i++)
    {
        (*this)[i] = v[i-begin];
    }
    return v;
}

Vec Vec::getSlice(int begin, int end)
{
    return (*this)[{begin, end}];
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

Vec Vec::operator+(Vec &b)
{
    assert(this->data.size() == b.data.size());
    vector<float> v(this->data.size());
    for(int i =0; i < v.size(); i++)
    {
        v[i] = (*this)[i] + b[i];
    }
    return Vec(v);
}

Vec Vec::operator-(Vec &b)
{
    assert(this->data.size() == b.data.size());
    vector<float> v(this->data.size());
    for(int i =0; i < v.size(); i++)
    {
        v[i] = (*this)[i] - b[i];
    }
    return Vec(v);
}

Vec Vec::operator*(float b)
{
    vector<float> v(this->data.size());
    for(int i =0; i < v.size(); i++)
    {
        v[i] = (*this)[i] * b;
    }
    return Vec(v);
}

Vec Vec::operator/(float b)
{
    assert(fabs(b - 0.0) > 1e-6);
    vector<float> v(this->data.size());
    for(int i =0; i < v.size(); i++)
    {
        v[i] = (*this)[i] / b;
    }
    return Vec(v);
}
