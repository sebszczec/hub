#include "context_manager.hpp"

namespace network
{

ContextManager::~ContextManager()
{
    this->ClearAllContexts();
}

void ContextManager::ClearAllContexts()
{
    for (auto &item : this->_contextContainer)
    {
        delete item.second;
    }

    this->_contextContainer.clear();
}

Context * ContextManager::CreateContext()
{
    auto id = this->_idGenerator++;
    auto context = new Context(id);
    this->_contextContainer[id] = context;

    return context;
}

void ContextManager::DeleteContext(Context * context)
{
    auto id = context->GetId();
    auto item = this->_contextContainer.find(id);

    if (item == this->_contextContainer.end())
    {
        return;
    }

    delete context;
    this->_contextContainer.erase(item);
}

unsigned int ContextManager::GetActiveCountextCount()
{
    return this->_contextContainer.size();
}

} // namespace network
