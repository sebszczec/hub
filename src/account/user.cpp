#include "user.hpp"

namespace account
{

AccessLevel & User::GetAccessLevel()
{
    return this->_accessLevel;
}

} // namespace account
