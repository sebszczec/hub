#ifndef __LS_COMMAND_TEST_HPP
#define __LS_COMMAND_TEST_HPP

#include <gtest/gtest.h>
#include "ls_command.hpp"
#include <iostream>
#include "system.hpp"

using commands::LsCommand;
using commands::CommandArgument;

class LsCommandTest : public testing::Test
{
public:
    LsCommand * sut;
public:
    LsCommandTest()
    {
        this->sut = new LsCommand();
    }

    ~LsCommandTest()
    {
        delete this->sut;
    }
};

TEST_F(LsCommandTest, Register)
{
    string expect = ".ls";
    auto result = sut->Register();
    EXPECT_STREQ(expect.c_str(), result.c_str());
}

TEST_F(LsCommandTest, PrintHelp)
{
    string expect = "shows all available commands";
    auto result = sut->PrintHelp();
    EXPECT_STREQ(expect.c_str(), result.c_str());        
}

TEST_F(LsCommandTest, Execute)
{
    CommandArgument arg;
    EXPECT_TRUE(sut->Execute(arg));
}

#endif