#include "context_manager.hpp"

ContextManager * ContextManager::_instance = nullptr;

ContextManager * ContextManager::GetInstance()
{
    if (ContextManager::_instance == nullptr)
    {
        ContextManager::_instance = new ContextManager();
    }

    return ContextManager::_instance;
}

void ContextManager::ClearInstance()
{
    if (ContextManager::_instance != nullptr)
    {
        delete ContextManager::_instance;
        ContextManager::_instance = nullptr;
    }
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
