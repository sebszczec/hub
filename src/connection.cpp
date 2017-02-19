#include "connection.hpp"

Connection::~Connection()
{
    if (this->_stream == nullptr)
    {
        return;
    }

    delete this->_stream;
    this->_stream = nullptr;
}

void TelnetConnection::HandleData(Block * block)
{

}