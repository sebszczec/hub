#include "user.hpp"

namespace account
{

AccessState & User::GetAccessState()
{
    return this->_accessState;
}

} // namespace account
