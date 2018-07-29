#ifndef __USER_TEST_HPP
#define __USER_TEST_HPP

#include <gtest/gtest.h>
#include "user.hpp"
#include <string>

using account::AccessLevel;
using account::User;
using namespace std;

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

TEST_F(UserTest, GetDafaultName)
{
    string expect = "";
    auto result = _sut->GetName();
    EXPECT_STREQ(expect.c_str(), result.c_str());
}

TEST_F(UserTest, SetName)
{
    string expect = "FooBaar";
    _sut->SetName(expect);

    auto result = _sut->GetName();
    EXPECT_STREQ(expect.c_str(), result.c_str());
}

#endif
