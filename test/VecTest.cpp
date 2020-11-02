//
// Created by 李喆昊 on 2020/11/1.
//
#include "../include/Vec.h"
#include "gtest/gtest.h"
#include <cmath>

using namespace ReNLA;

namespace {
    TEST(VecTest, Slice) {
        Vec x({1, 2, 3});
        EXPECT_EQ((x[{0, 2}]), Vec({1, 2})) << "x: " << x;

        x.setSlice(0, 2, Vec({2, 3}));
        EXPECT_EQ(x, Vec({2, 3, 3})) << "x: " << x;

        x.addToSlice(0, 2, -x[{0, 2}]);
        EXPECT_EQ(x, Vec({0, 0, 3})) << "x: " << x;

        x.mulToSlice(1, 3, 3);
        EXPECT_EQ(x, Vec({0, 0, 9})) << "x: " << x;
    };

    TEST(VecTest, add_and_minus) {
        Vec a({1, 2, 3, 4, 5, 6});
        Vec b({6, 5, 4, 3, 2, 1});
        EXPECT_EQ(a + b, Vec({7, 7, 7, 7, 7, 7}));
        EXPECT_EQ(a - b, Vec({-5, -3, -1, 1, 3, 5}));
        a += b;
        EXPECT_EQ(a, Vec({7, 7, 7, 7, 7, 7}));
        a += 10;
        EXPECT_EQ(a, Vec({17, 17, 17, 17, 17, 17}));
        EXPECT_EQ(10 + a, Vec({27, 27, 27, 27, 27, 27}));

        a += 10;
        a -= b;
        EXPECT_EQ(a, Vec({21, 22, 23, 24, 25, 26}));
        EXPECT_EQ(a - 10, Vec({11, 12, 13, 14, 15, 16}));

    }

    TEST(VecTest, multiply) {
        Vec a({1, 2, 3});
        EXPECT_EQ(a * 3, Vec({3, 6, 9}));
        a *= 3;
        EXPECT_EQ(a, Vec({3, 6, 9}));
        EXPECT_EQ(a * 2, Vec({6, 12, 18}));
        EXPECT_EQ(0.5 * a, Vec({1.5, 3, 4.5}));
    }

    TEST(VecTest, div) {
        Vec a({6, 9, 15});
        EXPECT_EQ(a / 3, Vec({2, 3, 5}));
        a /= 3;
        EXPECT_EQ(a, Vec({2, 3, 5}));
    }

    TEST(VecTest, max_and_min) {
        Vec x({1, 2, 3, 7, 6, 5});
        EXPECT_EQ(x.maxIdx(0, 3), 2);
        EXPECT_EQ(x.maxIdx(0, 6), 3);
        EXPECT_EQ(x.minIdx(3, 6), 5);

        Vec y({3400, -60000, 270000, -400000, 200000});
        EXPECT_EQ(y.maxAbsIdx(0, y.size()), 3);
    }

    TEST(VecTest, dot)
    {
        //TODO
    }

    TEST(VecTest, swap)
    {

    }

    TEST(VecTest, norm)
    {
        Vec x({-5, 1, 2, 3, 4});
        Vec y({3400, -60000, 270000, -400000, 200000});
        EXPECT_EQ(x.normInfin(), 5);
        EXPECT_EQ(y.normInfin(), 400000);
        EXPECT_EQ(x.norm1(), 15);
        EXPECT_EQ(x.dot(x), 25.0 + 1.0 + 4.0 + 9.0 + 16.0 );
        EXPECT_EQ(x.norm2(), sqrt(25.0 + 1.0 + 4.0 + 9.0 + 16.0));
    }
}

