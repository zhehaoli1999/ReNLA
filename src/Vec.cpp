//
// Created by 李喆昊 on 2020/10/2.
//

#include "../include/Vec.h"
#include <cmath>
#include <algorithm>
#include <utility>
using namespace ReNLA;

Vec::Vec(vector<double>v) : data{std::move(v)}
{}

Vec::Vec(int n)
{
    data = vector<double>(n, 0.0);
}

Vec::Vec(int n, double num)
{
    data = vector<double>(n, num);
}

Vec Vec::setOneHot(int idx) {
    assert(idx >=0 && idx < (*this).size());
    for(int i = 0; i < (*this).size(); i++)
    {
        if(i == idx) (*this)[i] = 1.0;
        else (*this)[i] = 0.0;
    }
    return (*this);
}

Vec Vec::setOne() {
    for(int i = 0; i < (*this).size(); i++)
    {
        (*this)[i] = 1.0;
    }
    return (*this);
}

Vec Vec::setIncremental()  {
    for(int i = 0; i < (*this).size(); i++)
    {
        (*this)[i] = i * 1.0;
    }
    return (*this);
}

int Vec::size()
{
    return data.size();
}
double& Vec::operator[](const int idx) {
    return this->data[idx];
}

Vec Vec::operator[](const pair<int, int> slice)
{
    assert(slice.second >= slice.first && slice.second <= (*this).size()
        && slice.first>=0);
    return Vec(vector(this->data.begin()+slice.first,
                        this->data.begin()+slice.second));
}

Vec Vec::setSlice(int begin, int end, Vec v)
{
    assert(v.data.size() == end - begin);
    for(int i = begin; i < end; i++)
    {
        (*this)[i] = v[i-begin];
    }
    return v;
}

Vec Vec::getSlice(int begin, int end)
{
    return (*this)[{begin, end}];
}

Vec Vec::addToSlice(int begin, int end, Vec v) {
    assert(v.data.size() == end - begin);
    for(int i = begin; i < end; i++)
    {
        (*this)[i] += v[i-begin];
    }
    return (*this)[{begin, end}];
}

Vec Vec::mulToSlice(int begin, int end, double a) {
    for(int i = begin; i < end; i++)
    {
        (*this)[i] *= a;
    }
    return (*this)[{begin, end}];
}

ostream& ReNLA::operator<<(ostream& os, Vec x)
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
    vector<double> v(this->data.size());
    for(int i =0; i < v.size(); i++)
    {
        v[i] = (*this)[i] + b[i];
    }
    return Vec(v);
}
Vec Vec::operator+(double b)
{
    vector<double> v(this->data.size());
    for(int i =0; i < v.size(); i++)
    {
        v[i] = (*this)[i] + b;
    }
    return Vec(v);
}

Vec Vec::operator-(double b)
{
    vector<double> v(this->data.size());
    for(int i =0; i < v.size(); i++)
    {
        v[i] = (*this)[i] - b;
    }
    return Vec(v);
}

Vec Vec::operator-()
{
    vector<double> v(this->data.size());
    for(int i =0; i < v.size(); i++)
    {
        v[i] = -(*this)[i];
    }
    return Vec(v);
}

Vec Vec::operator-(Vec &b)
{
    assert(this->data.size() == b.data.size());
    vector<double> v(this->data.size());
    for(int i =0; i < v.size(); i++)
    {
        v[i] = (*this)[i] - b[i];
    }
    return Vec(v);
}

Vec Vec::operator*(double b)
{
    vector<double> v(this->data.size());
    for(int i =0; i < v.size(); i++)
    {
        v[i] = (*this)[i] * b;
    }
    return Vec(v);
}

Vec Vec::operator/(double b)
{
    assert(fabs(b - 0.0) > eps);
    vector<double> v(this->data.size());
    for(int i =0; i < v.size(); i++)
    {
        v[i] = (*this)[i] / b;
    }
    return Vec(v);
}

int Vec::maxAbsIdx(int begin, int end)
{
    assert(begin >=0 && end >= begin && end <= (*this).size());
    int idx = begin;
    double max = fabs((*this)[begin]);
    for(int i = begin + 1; i < end; i++)
    {
        if(fabs((*this)[i]) > max)
            idx = i;
    }
    return idx;
}

int Vec::maxIdx(int begin, int end)
{
    assert(begin >=0 && end >= begin && end <= (*this).size());
    auto iter = std::max_element(this->data.begin() + begin,this->data.begin() + end);
    int idx = iter - this->data.begin();
    return idx;
}

int Vec::minIdx(int begin, int end)
{
    assert(begin >=0 && end >= begin && end <= (*this).size());
    auto iter = std::min_element(this->data.begin() + begin,this->data.begin() + end);
    int idx = iter - this->data.begin();
    return idx;
}
Vec Vec::swap(int idx1, int idx2)
{
    assert(idx1 >=0 && idx1 < (*this).size() && idx2 >=0 && idx2 <(*this).size());
    if(idx1 != idx2) {
        double temp = (*this)[idx1];
        (*this)[idx1] = (*this)[idx2];
        (*this)[idx2] = temp;
    }
    return (*this);
}

double Vec::dot(Vec b)
{
    assert((*this).size() == b.size());
    double dot = 0.0;
    for(int i = 0; i < b.size(); i++)
    {
        dot += (*this)[i] * b[i];
    }
    return dot;
}

double Vec::dist2(Vec &b) {
    return (*this - b).dot(*this - b);
}

double Vec::dist2(Vec &a, Vec &b) {
    return a.dist2(b);
}

double Vec::length() {
    return sqrt(dist2(*this, *this));
}