#ifndef __USER_HPP
#define __USER_HPP

#include "access_level.hpp"

namespace account
{

class User
{
private:
    AccessLevel _accessLevel;
public:
    User();
    ~User() = default;

    AccessLevel & GetAccessLevel();
};

} // namespace account

#endif
