#ifndef __CONNECTION_MANAGER_HPP
#define __CONNECTION_MANAGER_HPP

#include <libsocket/inetserverstream.hpp>
#include "memory_manager.hpp"
#include <map>

using namespace std;
using libsocket::inet_stream;

class Connection
{
    int _socketFd = 0;
    inet_stream * _stream = nullptr;

public:
    Connection(int socketFd, inet_stream * stream)
    : _socketFd(socketFd), _stream(stream)
    {}

    ~Connection()
    {
        if (this->_stream == nullptr)
        {
            return;
        }

        delete this->_stream;
        this->_stream = nullptr;
    }

    void HandleData(Block * block)
    {

    }
};

class ConnectionManager
{
private:
    map<int, Connection *> _connections;
public:
    ConnectionManager() = default;
    ~ConnectionManager() = default;

    void AddConnection(inet_stream * stream);
    void RemoveConnection(int socketFd);
    Connection * GetConnection(int socketFd);
    void ClearAllConnections();
};

#endif