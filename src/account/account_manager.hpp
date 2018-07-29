#ifndef ACCOUNT_MANAGER_HPP
#define ACCOUNT_MANAGER_HPP

#include <string>
#include <map>
#include "user.hpp"

namespace account
{

class UserInfo
{
public:
    std::string Username;
    std::string Password;
};

class AccountManager
{
private:
    std::map<std::string, UserInfo> _userInDB;
public:
    AccountManager() = default;
    ~AccountManager() = default;

    void RefreshWithDB();

    bool ValidateUser(const std::string & name, const std::string & password, account::User & user);
    void ClearUserCache();
};

} // namespace account

#endif
