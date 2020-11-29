//
// Created by 李喆昊 on 2020/10/2.
//
#ifndef CODES_VEC_H
#define CODES_VEC_H
#include <vector>
#include <iostream>
#include "../include/constValues.h"

using namespace std;

namespace ReNLA {
    class Vec {
    public:
        Vec();
        Vec(vector<long double>);
        Vec(int n);

        Vec setOneHot(int idx);
        Vec setIncremental();
        Vec setOne();
        Vec setNum(const long double);
        Vec setRandom(const long double min, const long double max);

        int size() const;

        long double operator[] (const int idx) const;
        long double& operator[](const int idx);
        Vec operator[](const pair<int, int>) const; // Vec slice

        Vec setSlice(int begin, int end, Vec v);
        Vec getSlice(int begin, int end);
        Vec addToSlice(int begin, int end, Vec v);
        Vec mulToSlice(int begin, int end, long double a);

        Vec operator-() const;
        Vec& operator+=(const Vec& b);
        Vec& operator+=(const long double t);
        Vec& operator-=(const Vec& b);
        Vec& operator-=(const long double t);

        Vec& operator*=(const long double b);
        Vec& operator/=(const long double b);

        friend ostream& operator<< (ostream& os, const Vec&);
        friend Vec operator+ (const Vec& a, const Vec& b);
        friend Vec operator+ (const Vec& a, const long double t);
        friend Vec operator+ (const long double t, const Vec& a);

        friend Vec operator- (const Vec& a, const Vec& b);
        friend Vec operator- (const Vec& a, long double t);
        friend Vec operator- (const long double t, const Vec& a);

        friend Vec operator* (const Vec& v, const long double t);
        friend Vec operator* (const long double t, const Vec& v);
        friend Vec operator/ (const Vec& v, const long double t);

        friend bool operator== (const Vec& a, const Vec& b);

        long double normInfin() const;
        long double norm2() const;
        long double norm1() const;
        long double dist2(const Vec& b) const;
        static long double dist2(const Vec& a, const Vec& b);
        long double length() const;
        Vec& normalize();
        long double dot(const Vec& b) const;

        int maxAbsIdx(int begin, int end) const;
        int maxIdx(int begin, int end) const ;
        int minIdx(int begin, int end) const;
        long double absMax() const;

        Vec getSign() const;

        Vec swap(int idx1, int idx2);

    private:
        vector<long double> data;
    };
}


#endif //CODES_VEC_H
