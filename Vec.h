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

        float& operator[](const int idx);
        Vec operator[](const pair<int, int>);

        friend ostream& operator<< (ostream& os, Vec);

        float norm2();
        float norm1();
        float dist(Vec& b);
        Vec normalize();
        float dot(Vec& b);

        Vec operator+(Vec& b);
        Vec operator-(Vec& b);

    private:
        vector<float> data;
    };
}


#endif //CODES_VEC_H
