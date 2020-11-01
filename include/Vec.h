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
        Vec(vector<double>);
        Vec(int n);

        Vec setOneHot(int idx);
        Vec setIncremental();
        Vec setOne();
        Vec setNum(const double);

        int size() const;

        double operator[] (const int idx) const;
        double& operator[](const int idx);
        Vec operator[](const pair<int, int>) const; // Vec slice

        Vec setSlice(int begin, int end, Vec v);
        Vec getSlice(int begin, int end);
        Vec addToSlice(int begin, int end, Vec v);
        Vec mulToSlice(int begin, int end, double a);

        Vec operator-() const;
        Vec& operator+=(const Vec& b);
        Vec& operator+=(const double t);
        Vec& operator-=(const Vec& b);
        Vec& operator-=(const double t);

        Vec& operator*=(const double b);
        Vec& operator/=(const double b);

        friend ostream& operator<< (ostream& os, const Vec&);
        friend Vec operator+ (const Vec& a, const Vec& b);
        friend Vec operator+ (const Vec& a, const double t);
        friend Vec operator+ (const double t, const Vec& a);

        friend Vec operator- (const Vec& a, const Vec& b);
        friend Vec operator- (const Vec& a, double t);
        friend Vec operator- (const double t, const Vec& a);

        friend Vec operator* (const Vec& v, const double t);
        friend Vec operator* (const double t, const Vec& v);
        friend Vec operator/ (const Vec& v, const double t);

        friend bool operator== (const Vec& a, const Vec& b);

        double norm2();
        double norm1();
        double dist2(Vec& b);
        static double dist2(Vec& a, Vec& b);
        double length();
        Vec normalize();
        double dot(Vec b);

        int maxAbsIdx(int begin, int end);
        int maxIdx(int begin, int end);
        int minIdx(int begin, int end);

        Vec swap(int idx1, int idx2);

    private:
        vector<double> data;
    };
}


#endif //CODES_VEC_H
