#ifndef __CONTEXT_MANAGER_HPP
#define __CONTEXT_MANAGER_HPP

#include "context.hpp"
#include <map>

using namespace std;

namespace network
{

class ContextManager
{
private:
    ContextManager() = default;
    ~ContextManager() = default;

    static ContextManager * _instance;
    unsigned int _idGenerator = 0;
    map<unsigned int, Context *> _contextContainer;

    void ClearAllContexts();
    
    static ContextManager * GetInstance(); 

public:
    static ContextManager * GetInstance2();
    static void ClearInstance();

    Context * CreateContext();
    void DeleteContext(Context * context);
    void DeleteAllContexts();
    unsigned int GetActiveCountextCount();
};

} // namespace network

#endif
