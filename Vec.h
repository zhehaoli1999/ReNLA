//
// Created by 李喆昊 on 2020/10/2.
//
#ifndef CODES_VEC_H
#define CODES_VEC_H
#include <vector>
#include <iostream>

using namespace std;

namespace NLA {
    class Vec {
    public:
        Vec(vector<float>);
        Vec(int n);

        int size();

        float& operator[](const int idx);
        Vec operator[](const pair<int, int>); // Vec slice

        Vec setSlice(int begin, int end, Vec v);
        Vec getSlice(int begin, int end);
        Vec addToSlice(int begin, int end, Vec v);
        Vec mulToSlice(int begin, int end, float a);

        friend ostream& operator<< (ostream& os, Vec);
        Vec operator+(Vec& b);
        Vec operator+(float b);

        Vec operator-(Vec& b);
        Vec operator-(float b);
        Vec operator-();

        Vec operator*(float b);
        Vec operator/(float b);

        float norm2();
        float norm1();
        float dist(Vec& b);
        Vec normalize();
        float dot(Vec& b);

    private:
        vector<float> data;
    };
}


#endif //CODES_VEC_H
