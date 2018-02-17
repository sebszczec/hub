#ifndef __ACCESS_LEVEL_TEST_HPP
#define __ACCESS_LEVEL_TEST_HPP

#include <gtest/gtest.h>
#include "access_level.hpp"

using account::AccessLevel;

class AccessLevelTest : public testing::Test 
{
protected:
    AccessLevel * _sut = nullptr;
public:
    void SetUp() override
    {
        _sut = new AccessLevel();
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

TEST_F(AccessLevelTest, DefaultLevel)
{
    EXPECT_EQ(AccessLevel::Level::NotLogged, _sut->GetLevel());
}

TEST_F(AccessLevelTest, SetLevel)
{
    _sut->SetLevel(AccessLevel::Level::User);
    EXPECT_EQ(AccessLevel::Level::User, _sut->GetLevel());

    _sut->SetLevel(AccessLevel::Level::Administrator);
    EXPECT_EQ(AccessLevel::Level::Administrator, _sut->GetLevel());
}

#endif
