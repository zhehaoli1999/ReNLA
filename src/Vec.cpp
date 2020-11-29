//
// Created by 李喆昊 on 2020/10/2.
//

#include "../include/Vec.h"
#include <cmath>
#include <algorithm>
#include <utility>
#include <random>
using namespace ReNLA;

Vec::Vec() : data{0}
{

}
Vec::Vec(vector<long double>v) : data{std::move(v)}
{}

Vec::Vec(int n)
{
    data = vector<long double>(n, 0.0);
}

//Vec::Vec(int n, long double num)
//{
//    data = vector<long double>(n, num);
//}

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
    return (*this).setNum(1.0);
}

Vec Vec::setNum(const long double num) {
    for(int i = 0; i < (*this).size(); i++)
    {
        (*this)[i] = num;
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

Vec Vec::setRandom(const long double min, const long double max) {
    assert(max > min);
    std::uniform_real_distribution<long double> distribution(min, max);
    std::mt19937 generator;
    for(int i =0 ; i < this->size(); i++)
        (*this)[i] = distribution(generator);

    return (*this);
}
int Vec::size() const
{
    return data.size();
}

long double Vec::operator[](const int idx) const {
    return this->data[idx];
}
long double& Vec::operator[](const int idx) {
    return this->data[idx];
}

Vec Vec::operator[](const pair<int, int> slice) const
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
    return (*this);
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

Vec Vec::mulToSlice(int begin, int end, long double a) {
    for(int i = begin; i < end; i++)
    {
        (*this)[i] *= a;
    }
    return (*this)[{begin, end}];
}

ostream& ReNLA::operator<<(ostream& os, const Vec& x)
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

Vec ReNLA::operator+(const Vec& a, const Vec &b)
{
    assert(a.size() == b.size());
    vector<long double> v(a.size());
    for(int i =0; i < v.size(); i++)
    {
        v[i] = a[i] + b[i];
    }
    return Vec(v);
}

Vec ReNLA::operator+(const Vec& a, const long double t)
{
    vector<long double> v(a.size());
    for(int i =0; i < v.size(); i++)
    {
        v[i] = a[i] + t;
    }
    return Vec(v);
}

Vec ReNLA::operator+(const long double t, const Vec& a)
{
    return a + t;
}

Vec ReNLA::operator-(const Vec& a, const Vec &b)
{
    assert(a.size() == b.size());
    vector<long double> v(a.size());
    for(int i =0; i < v.size(); i++)
    {
        v[i] = a[i] - b[i];
    }
    return Vec(v);
}

Vec ReNLA::operator-(const Vec& a, const long double t)
{
    vector<long double> v(a.size());
    for(int i =0; i < v.size(); i++)
    {
        v[i] = a[i] - t;
    }
    return Vec(v);
}

Vec ReNLA::operator-(const long double t, const Vec& a)
{
    return a - t;
}

Vec ReNLA::operator* (const Vec& a, const long double t)
{
    vector<long double> v(a.size());
    for(int i =0; i < v.size(); i++)
    {
        v[i] = a[i] * t;
    }
    return Vec(v);
}

Vec ReNLA::operator* (const long double t, const Vec& a)
{
    return  a * t;
}
Vec ReNLA::operator/ (const Vec& a, const long double t)
{
    assert(fabs(t - 0.0) > eps);
    vector<long double> v(a.size());
    for(int i =0; i < v.size(); i++)
    {
        v[i] = a[i] / t;
    }
    return Vec(v);
}

bool ReNLA::operator==(const Vec &a, const Vec &b)
{
    if(a.size() != b.size()) return false;
    else
    {
        for(int i = 0; i < a.size(); i++)
        {
            if(fabs(a[i] - b[i]) > eps) return false;
            // TODO: maybe a[i] != b[i] also works here?
        }
        return true;
    }
}

Vec Vec::operator-() const{
    vector<long double> v(this->size());
    for(int i = 0; i < this->size(); i++)
    {
        v[i] = -(*this)[i];
    }
    return Vec(v);
}

Vec& Vec::operator+=(const Vec& b)
{
    assert((*this).size() == b.size());
    for(int i =0; i <  (*this).size(); i++)
    {
        (*this)[i] += b[i];
    }
    return *this;
}

Vec& Vec::operator+=(const long double t)
{
    for(int i =0; i <  (*this).size(); i++)
    {
        (*this)[i] += t;
    }
    return *this;
}

Vec& Vec::operator-=(const Vec& b)
{
    return (*this) += -b;
}


Vec& Vec::operator-=(const long double t)
{
    for(int i =0; i <  (*this).size(); i++)
    {
        (*this)[i] -= t;
    }
    return *this;
}

Vec& Vec::operator*=(const long double t)
{
    for(int i =0; i <  (*this).size(); i++)
    {
        (*this)[i] *= t;
    }
    return *this;
}

Vec& Vec::operator/=(const long double t)
{
    assert(fabs(t - 0.0) > eps);
    for(int i =0; i <  (*this).size(); i++)
    {
        (*this)[i] /= t;
    }
    return *this;
}

int Vec::maxAbsIdx(int begin, int end) const
{
    assert(begin >=0 && end >= begin && end <= (*this).size());
    int idx = begin;
    long double max = fabs((*this)[begin]);
    for(int i = begin + 1; i < end; i++)
    {
        auto t = fabs((*this)[i]);
        if( t > max) {
            idx = i;
            max = t;
        }
    }
    return idx;
}

int Vec::maxIdx(int begin, int end) const
{
    assert(begin >=0 && end >= begin && end <= (*this).size());
    auto iter = std::max_element(this->data.begin() + begin,this->data.begin() + end);
    int idx = iter - this->data.begin();
    return idx;
}

int Vec::minIdx(int begin, int end) const
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
        long double temp = (*this)[idx1];
        (*this)[idx1] = (*this)[idx2];
        (*this)[idx2] = temp;
    }
    return (*this);
}

long double Vec::dot(const Vec& b) const
{
    assert((*this).size() == b.size());
    long double dot = 0.0;
    for(int i = 0; i < b.size(); i++)
    {
        dot += (*this)[i] * b[i];
    }
    return dot;
}

long double Vec::dist2(const Vec &b) const {
    return (*this - b).dot(*this - b);
}

long double Vec::dist2(const Vec &a, const Vec &b) {
    return a.dist2(b);
}

long double Vec::length() const {
    return sqrt((*this).dot(*this));
}

Vec Vec::getSign() const
{
    Vec signV(this->size());
    for(int i = 0 ; i < this->size(); i++)
    {
        ((*this)[i] >= 0) ? (signV[i] = 1.0) : (signV[i] = -1.0);
    }
    return signV;
}

long double Vec::absMax() const {
    int idx = (*this).maxAbsIdx(0, this->size());
    return fabs((*this)[idx]);
}

long double Vec::norm1() const{
    long double n1 = 0.0;
    for(int i = 0; i < (*this).size(); i++)
    {
        n1 += fabs((*this)[i]);
    }
    return n1;
}

long double Vec::normInfin() const {
    return (*this).absMax();
}

long double Vec::norm2() const {
    return this->length();
}

Vec& Vec::normalize() {
    return (*this) /= (*this).norm2();
}