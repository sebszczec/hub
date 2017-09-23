#ifndef __CONTEXT_HPP
#define __CONTEXT_HPP

namespace network
{

class Context
{
private:
    unsigned int _id = -1;
public:
    Context(unsigned int id);
    
    ~Context() = default;

    unsigned int GetId()
    {
        return this->_id;
    }
};

} // namespace network

#endif
