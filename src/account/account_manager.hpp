#ifndef ACCOUNT_MANAGER_HPP
#define ACCOUNT_MANAGER_HPP

#include <string>
#include <map>

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

    bool ValidateUser(std::string name, std::string password);
    void ClearUserCache();
};

} // namespace account

#endif
