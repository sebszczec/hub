#include "iconnection.hpp"
#include "logger.hpp"

IConnection::~IConnection()
{
    ContextManager::GetInstance()->DeleteContext(this->_context);
    this->_context = nullptr;

    if (this->_stream == nullptr)
    {
        return;
    }

    delete this->_stream;
    this->_stream = nullptr;
}

inet_stream & IConnection::GetStream()
{
    return *this->_stream;
}

Context * IConnection::GetContext()
{
    return this->_context;
}