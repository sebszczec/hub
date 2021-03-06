#include "user.hpp"

namespace account
{
    User::User()
    {
        this->_accessLevel.SetLevel(AccessLevel::Level::NotLogged);
        this->_name = "";
    }

    AccessLevel & User::GetAccessLevel()
    {
        return this->_accessLevel;
    }

    const std::string & User::GetName()
    {
        return this->_name;
    }

    void User::SetName(const std::string & name)
    {
        this->_name = std::move(name);
    }

    const User::UserType & User::GetUserType()
    {
        return this->_type;
    }

    void User::SetUserType(const User::UserType & type)
    {
        this->_type = type;
    }

} // namespace account
