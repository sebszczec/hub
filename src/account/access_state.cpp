#include "access_state.hpp"

namespace account
{

AccessState::State AccessState::GetState()
{
    return this->_state;
}

void AccessState::SetState(const AccessState::State & state)
{
    this->_state = state;
}

} // namespace account
