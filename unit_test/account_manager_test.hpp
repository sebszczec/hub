#ifndef __ACCOUNT_MANAGER_TEST_HPP
#define __ACCOUNT_MANAGER_TEST_HPP

#include <gtest/gtest.h>
#include "account_manager.hpp"
#include "system.hpp"

using namespace account;

class AccountManagerTest : public testing::Test 
{
protected:
    AccountManager * _sut = nullptr;
public:
    void SetUp() override
    {
        _sut = new AccountManager();
        _sut->ClearUserCache();
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

TEST_F(AccountManagerTest, ValidateDummyUser)
{   
    User user; 
    std::string name = "dummy_name";
    std::string password = "dummy_password";
    EXPECT_FALSE(_sut->ValidateUser(name, password, user));
}

TEST_F(AccountManagerTest, ValidateWrongUser)
{
    User user; 
    _sut->RefreshWithDB();
    std::string name = "slaugh__";
    std::string password = "dummy_password";
    EXPECT_FALSE(_sut->ValidateUser(name, password, user));
}

TEST_F(AccountManagerTest, ValidateWrongPassword)
{
    User user; 
    _sut->RefreshWithDB();
    std::string name = "slaugh";
    std::string password = "dummy_password";
    EXPECT_FALSE(_sut->ValidateUser(name, password, user));
}

TEST_F(AccountManagerTest, ValidateUser)
{
    User user; 
    _sut->RefreshWithDB();
    std::string name = "slaugh";
    std::string password = "seb666";
    EXPECT_TRUE(_sut->ValidateUser(name, password, user));

    auto result = user.GetName();
    EXPECT_STREQ(name.c_str(), result.c_str());
}

#endif
