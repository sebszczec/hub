#ifndef __USER_HPP
#define __USER_HPP

#include "access_level.hpp"
#include <string>

namespace account
{

class User
{
public:
    enum UserType 
    {
        NotSet,
        Telnet,
        Mobile
    };

private:
    AccessLevel _accessLevel;
    std::string _name = "not set";
    UserType _type = UserType::NotSet;

public:
    User();
    ~User() = default;

    AccessLevel & GetAccessLevel();
    const std::string & GetName();
    void SetName(const std::string &);
    const UserType & GetUserType();
    void SetUserType(const UserType &);
};

} // namespace account

#endif
