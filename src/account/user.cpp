#include "user.hpp"

namespace account
{
    User::User()
    {
        this->_accessLevel.SetLevel(AccessLevel::Level::NotLogged);
    }

    AccessLevel & User::GetAccessLevel()
    {
        return this->_accessLevel;
    }

} // namespace account
