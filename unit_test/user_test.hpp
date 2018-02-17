#ifndef __USER_TEST_HPP
#define __USER_TEST_HPP

#include <gtest/gtest.h>
#include "user.hpp"

using account::AccessLevel;
using account::User;

class UserTest : public testing::Test 
{
protected:
    User * _sut = nullptr;
public:
    void SetUp() override
    {
        _sut = new User();
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

TEST_F(UserTest, DefaultLevel)
{
    EXPECT_EQ(AccessLevel::Level::NotLogged, _sut->GetAccessLevel().GetLevel());
}


#endif
