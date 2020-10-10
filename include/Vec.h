//
// Created by 李喆昊 on 2020/10/2.
//
#ifndef CODES_VEC_H
#define CODES_VEC_H
#include <vector>
#include <iostream>

using namespace std;

constexpr double eps = 1e-40;

namespace ReNLA {
    class Vec {
    public:
        Vec(vector<double>);
        Vec(int n);
        Vec(int n, double num);

        Vec setOneHot(int idx);
        Vec setIncremental();
        Vec setOne();

        int size();

        double& operator[](const int idx);
        Vec operator[](const pair<int, int>); // Vec slice

        Vec setSlice(int begin, int end, Vec v);
        Vec getSlice(int begin, int end);
        Vec addToSlice(int begin, int end, Vec v);
        Vec mulToSlice(int begin, int end, double a);

        friend ostream& operator<< (ostream& os, Vec);
        Vec operator+(Vec& b);
        Vec operator+(double b);

        Vec operator-(Vec& b);
        Vec operator-(double b);
        Vec operator-();

        Vec operator*(double b);
        Vec operator/(double b);

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
