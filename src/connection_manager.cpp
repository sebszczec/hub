#include "connection_manager.hpp"

void ConnectionManager::AddConnection(inet_stream * stream)
{
    auto descriptor = stream->getfd();
    auto connection = new Connection(descriptor, stream);
    this->_connections[descriptor] = connection;
}

void ConnectionManager::RemoveConnection(int socketFd)
{
    auto item = this->_connections.find(socketFd);
    if (item == this->_connections.end())
    {
        return;
    }

    delete item->second;
    this->_connections.erase(item);
}

void ConnectionManager::ClearAllConnections()
{
    for (auto &item : this->_connections)
    {
        delete item.second;
    }

    this->_connections.clear();
}