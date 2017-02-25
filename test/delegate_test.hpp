#ifndef __DELEGATE_TEST_HPP
#define __DELEGATE_TEST_HPP

#include <gtest/gtest.h>
#include "delegate.hpp"
#include <iostream>

using namespace std;

class DelegateTest : public testing::Test
{

};

TEST_F(DelegateTest, addMethodAndRunNoArgs)
{
    Delegate delegate;
    int b = 100;

    delegate.AddMethod([&b]()
        {
            b++;
        });

    delegate.Run();

    EXPECT_EQ(101, b);
}

TEST_F(DelegateTest, addMethodAndRun)
{
    Delegate delegate;
    int b = 100;
    int tmp = 20;

    delegate.AddMethod([&b](int a)
        {
            b += a;
        }, tmp);

    delegate.Run();

    EXPECT_EQ(100 + tmp, b);
}

TEST_F(DelegateTest, addTwoMethodsAndRun)
{
    Delegate delegate;
    int b = 100;
    int c = 1;

    delegate.AddMethod([&b]()
        {
            b++;
        });

    delegate.AddMethod([&c](int a)
        {
            c -= a;
        }, 10);

    delegate.Run();

    EXPECT_EQ(101, b);
    EXPECT_EQ(-9, c);
}

#endif