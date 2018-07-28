#ifndef __LOGOUT_COMMAND_TEST_HPP
#define __LOGOUT_COMMAND_TEST_HPP

#include <gtest/gtest.h>
#include "logout_command.hpp"
#include <iostream>
#include <thread>
#include "system.hpp"

using commands::LogoutCommand;
using commands::CommandArgument;

class LogoutCommandTest : public testing::Test
{
public:
    LogoutCommand * sut;
public:
    LogoutCommandTest()
    {
        this->sut = new LogoutCommand();
    }

    ~LogoutCommandTest()
    {
        delete this->sut;
    }
};


TEST_F(LogoutCommandTest, Register)
{
    string expect = ".logout";
    auto result = sut->Register();
    EXPECT_STREQ(expect.c_str(), result.c_str());
}

TEST_F(LogoutCommandTest, PrintHelp)
{
    string expect = "logout from system";
    auto result = sut->PrintHelp();
    EXPECT_STREQ(expect.c_str(), result.c_str());
}

TEST_F(LogoutCommandTest, AccessLevel)
{
    EXPECT_EQ(account::AccessLevel::Level::User, sut->GetAccessLevel());
}


TEST_F(LogoutCommandTest, Logout)
{
    string expect = "logout successful";
    
    CommandArgument arg;
    arg.Context = new network::Context(0);

    EXPECT_TRUE(sut->Execute(arg));
    auto result = sut->GetResult();
    
    EXPECT_STREQ(expect.c_str(), result.c_str());

    delete arg.Context;
}

#endif // __LOGOUT_COMMAND_TEST_HPP
