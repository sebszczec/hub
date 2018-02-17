#ifndef __ACCESS_LEVEL_HPP
#define __ACCESS_LEVEL_HPP

namespace account
{

class AccessLevel
{
private:
public:
    enum Level
    {
        NotLogged,
        User,
        Administrator
    };

    AccessLevel() = default;
    ~AccessLevel() = default;

    Level GetLevel();
    void SetLevel(const Level &);

private:
    Level _level = Level::NotLogged;
};

} // namespace account

#endif
