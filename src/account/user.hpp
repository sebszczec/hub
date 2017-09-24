#ifndef __USER_HPP
#define __USER_HPP

#include "access_state.hpp"

namespace account
{

class User
{
private:
    AccessState _accessState;
public:
    User() = default;
    ~User() = default;

    AccessState & GetAccessState();
};

} // namespace account

#endif
