#ifndef __COMMAND_MANAGER_TEST
#define __COMMAND_MANAGER_TEST

#include <gtest/gtest.h>
#include "command_manager.hpp"
#include "uptime_command.hpp"
#include "login_command.hpp"
#include "system.hpp"

using namespace commands;

class CommandManagerTest : public testing::Test 
{
protected:
    CommandManager * _sut = nullptr;
public:
    void SetUp() override
    {
        _sut = new CommandManager();
    }

    void TearDown() override
    {
        if (_sut != nullptr)
        {
            delete _sut;
            _sut = nullptr;
        }
    }
};

TEST_F(CommandManagerTest, Empty1)
{
    auto result = _sut->GetRegisteredCommands();
    EXPECT_EQ(0, result.size());
}

TEST_F(CommandManagerTest, Empty2)
{
    auto command = "FooBar";
    string result = "";

    EXPECT_FALSE(_sut->GetCommandHelp(command, result));
}

TEST_F(CommandManagerTest, Empty3)
{
    auto command = "FooBar";
    CommandArgument arg;
    CommandExecutionResult result;

    EXPECT_FALSE(_sut->ExecuteCommand(command, arg, result));
    EXPECT_FALSE(result.Success);

    string expected = "command does not exist!";
    EXPECT_STREQ(expected.c_str(), result.ErrorMessage.c_str());
}

TEST_F(CommandManagerTest, GetRegisteredCommands)
{
    _sut->RegisterCommand(new UptimeCommand());
    _sut->RegisterCommand(new LoginCommand());
    auto result = _sut->GetRegisteredCommands();
    EXPECT_EQ(2, result.size());
   
   string expected = ".uptime";
   EXPECT_STREQ(expected.c_str(), result[0].c_str());

   expected = ".login";
   EXPECT_STREQ(expected.c_str(), result[1].c_str());
}

TEST_F(CommandManagerTest, ExecuteCommand)
{
    auto command = new UptimeCommand();
    _sut->RegisterCommand(command);

    auto name = command->Register();
    
    CommandArgument arg;
    arg.Context = new network::Context(0);

    CommandExecutionResult result;
    EXPECT_FALSE(_sut->ExecuteCommand(name, arg, result));
    EXPECT_FALSE(result.Success);

    string expected = "no access to run " + name;
    EXPECT_STREQ(expected.c_str(), result.ErrorMessage.c_str());

    delete arg.Context;
}

#endif
