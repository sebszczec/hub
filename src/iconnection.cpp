#include "iconnection.hpp"
#include "logger.hpp"

IConnection::~IConnection()
{
    if (this->_stream == nullptr)
    {
        return;
    }

    delete this->_stream;
    this->_stream = nullptr;
}
