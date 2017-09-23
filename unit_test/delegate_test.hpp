#ifndef __DELEGATE_TEST_HPP
#define __DELEGATE_TEST_HPP

#include <gtest/gtest.h>
#include "delegate.hpp"
#include <iostream>

using namespace std;
using tools::Delegate;
using tools::DelegateArgument;

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
            argument.Sender = (void *)0xdeadbeef;
            b += a;
        }, arg, tmp);
    
    DelegateArgument argumentToRun;
    argumentToRun.Sender = nullptr;
    delegate.Run(argumentToRun);

    EXPECT_TRUE(argumentToRun.Sender == (void *)0xdeadbeef);
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