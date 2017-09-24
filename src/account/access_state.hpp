#ifndef __ACCESS_STATE_HPP
#define __ACCESS_STATE_HPP

namespace account
{

class AccessState
{
private:
public:
    enum State
    {
        NotLogged,
        User,
        Administrator
    };

    AccessState() = default;
    ~AccessState() = default;

    State GetState();
    void SetState(const State &);

private:
    State _state = State::NotLogged;
};

} // namespace account

#endif
