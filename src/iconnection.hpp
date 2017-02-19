#ifndef __CONNECTION_HPP
#define __CONNECTION_HPP

#include <libsocket/inetserverstream.hpp>
#include "memory_manager.hpp"

class ConnectionManager;

using namespace std;
using libsocket::inet_stream;

class IConnection
{
protected:
    int _socketFd = 0;
    inet_stream * _stream = nullptr;
    ConnectionManager * _parent;

public:
    IConnection(int socketFd, inet_stream * stream, ConnectionManager * parent)
    : _socketFd(socketFd), _stream(stream), _parent(parent)
    {}

    virtual ~IConnection();

    virtual void HandleData(Block * block) = 0;
};

#endif
