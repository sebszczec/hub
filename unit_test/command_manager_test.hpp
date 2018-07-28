#ifndef __COMMAND_MANAGER_TEST
#define __COMMAND_MANAGER_TEST

#include <gtest/gtest.h>
#include "command_manager.hpp"
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

#endif
