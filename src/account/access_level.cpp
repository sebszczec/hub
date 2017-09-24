#include "access_level.hpp"

namespace account
{

    AccessLevel::Level AccessLevel::GetLevel()
{
    return this->_level;
}

void AccessLevel::SetLevel(const AccessLevel::Level & level)
{
    this->_level = level;
}

} // namespace account
