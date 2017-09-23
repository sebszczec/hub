#ifndef __UPTIME_COMMAND_TEST_HPP
#define __UPTIME_COMMAND_TEST_HPP

#include <gtest/gtest.h>
#include "uptime_command.hpp"
#include <iostream>
#include <thread>

class UptimeCommandTest : public testing::Test
{
public:
    UptimeCommand * sut;
public:
    UptimeCommandTest()
    {
        this->sut = new UptimeCommand();
    }

    ~UptimeCommandTest()
    {
        delete this->sut;
    }
};


TEST_F(UptimeCommandTest, Register)
{
    string expect = ".uptime";
    auto result = sut->Register();
    EXPECT_STREQ(expect.c_str(), result.c_str());
}

TEST_F(UptimeCommandTest, PrintHelp)
{
    string expect = "shows how long applications works";
    auto result = sut->PrintHelp();
    EXPECT_STREQ(expect.c_str(), result.c_str());
}

TEST_F(UptimeCommandTest, Execute)
{
    string expect = "";
    CommandArgument arg;

    EXPECT_TRUE(sut->Execute(arg));
    auto result = sut->GetResult();
    
    EXPECT_STRNE(expect.c_str(), result.c_str());
}

TEST_F(UptimeCommandTest, GetResult_empty)
{
    string expect = "";
    
    auto result = sut->GetResult();
    EXPECT_STREQ(expect.c_str(), result.c_str());
}

#endif
