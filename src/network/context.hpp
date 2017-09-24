#ifndef __CONTEXT_HPP
#define __CONTEXT_HPP

#include "user.hpp"

namespace network
{

class Context
{
private:
    unsigned int _id = -1;
    account::User _user;
public:
    Context(unsigned int id);
    
    ~Context() = default;

    unsigned int GetId()
    {
        return this->_id;
    }

    account::User & GetUser()
    {
        return this->_user;
    }
};

} // namespace network

#endif
