#ifndef __USER_HPP
#define __USER_HPP

#include "access_level.hpp"
#include <string>

namespace account
{

class User
{
private:
    AccessLevel _accessLevel;
    std::string _name;
public:
    User();
    ~User() = default;

    AccessLevel & GetAccessLevel();
    const std::string & GetName();
    void SetName(const std::string &);
};

} // namespace account

#endif
