#include "connection_manager.hpp"

namespace network
{

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

IConnection * ConnectionManager::GetConnection(int socketFd)
{
    auto item = this->_connections.find(socketFd);
    
    if (item == this->_connections.end())
    {
        throw ConnectionNotFoundException();
    }

    return item->second;
}

map<int, IConnection *> & ConnectionManager::GetConnections()
{
    return this->_connections;
}

unsigned int ConnectionManager::GetNumberOfConnections()
{
    return this->_connections.size();
}

} // namespace network