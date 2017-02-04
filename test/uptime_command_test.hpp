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
    string expect = "Shows time how long service works on.\nUsage: .uptime\n";
    auto result = sut->PrintHelp();
    EXPECT_STREQ(expect.c_str(), result.c_str());
}

TEST_F(UptimeCommandTest, Execute)
{
    string expect = "";

    EXPECT_TRUE(sut->Execute());
    auto result = sut->GetResult();
    
    std::cout << result << std::endl;

    EXPECT_STRNE(expect.c_str(), result.c_str());
}

TEST_F(UptimeCommandTest, GetResult_empty)
{
    string expect = "";
    auto result = sut->GetResult();
    EXPECT_STREQ(expect.c_str(), result.c_str());
}

#endif
