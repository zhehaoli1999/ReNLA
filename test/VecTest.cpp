//
// Created by 李喆昊 on 2020/11/1.
//
#include "../include/Vec.h"
#include "gtest/gtest.h"

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
    }

    TEST(VecTest, dot_and_norm)
    {
        //TODO
    }

    TEST(VecTest, swap)
    {

    }
}

