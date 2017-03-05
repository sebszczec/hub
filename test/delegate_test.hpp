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
    DelegateArgument arg;

    delegate.AddMethod([&b](DelegateArgument & argument)
        {
            b++;
        }, arg);

    DelegateArgument argumentToRun;
    delegate.Run(argumentToRun);

    EXPECT_EQ(101, b);
}

TEST_F(DelegateTest, addMethodAndRun)
{
    Delegate delegate;
    int b = 100;
    int tmp = 20;
    DelegateArgument arg;

    delegate.AddMethod([&b](DelegateArgument & argument, int a)
        {
            argument.Sender = 1;
            b += a;
        }, arg, tmp);
    
    DelegateArgument argumentToRun;
    argumentToRun.Sender = 10;
    delegate.Run(argumentToRun);

    EXPECT_EQ(1, argumentToRun.Sender);
    EXPECT_EQ(100 + tmp, b);
}

TEST_F(DelegateTest, addTwoMethodsAndRun)
{
    Delegate delegate;
    int b = 100;
    int c = 1;
    DelegateArgument arg;

    delegate.AddMethod([&b](DelegateArgument & argument)
        {
            b++;
        }, arg);

    delegate.AddMethod([&c](DelegateArgument & argument, int a)
        {
            c -= a;
        }, arg, 10);

    DelegateArgument argumentToRun;
    delegate.Run(argumentToRun);

    EXPECT_EQ(101, b);
    EXPECT_EQ(-9, c);
}

#endif