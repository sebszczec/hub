#ifndef __WHOAMI_COMMAND_TEST_HPP
#define __WHOAMI_COMMAND_TEST_HPP

#include <gtest/gtest.h>
#include "whoami_command.hpp"
#include <iostream>
#include "system.hpp"

using commands::WhoamiCommand;
using commands::CommandArgument;

class WhoamiCommandTest : public testing::Test
{
public:
    WhoamiCommand * sut;
public:
    WhoamiCommandTest()
    {
        this->sut = new WhoamiCommand();
    }

    ~WhoamiCommandTest()
    {
        delete this->sut;
    }
};

TEST_F(WhoamiCommandTest, Register)
{
    string expect = ".whoami";
    auto result = sut->Register();
    EXPECT_STREQ(expect.c_str(), result.c_str());
}

TEST_F(WhoamiCommandTest, PrintHelp)
{
    string expect = "displays who you are";
    auto result = sut->PrintHelp();
    EXPECT_STREQ(expect.c_str(), result.c_str());
}

TEST_F(WhoamiCommandTest, AccessLevel)
{
    EXPECT_EQ(account::AccessLevel::Level::User, sut->GetAccessLevel());
}

TEST_F(WhoamiCommandTest, Whoami)
{
    string expect = "slaugh";
    
    CommandArgument arg;
    arg.Context = new network::Context(0);
    arg.Context->GetUser().SetName(expect);

    EXPECT_TRUE(sut->Execute(arg));
    auto result = sut->GetResult();
    
    EXPECT_STREQ(expect.c_str(), result.c_str());

    delete arg.Context;
}

#endif