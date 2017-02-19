#ifndef __CONNECTION_HPP
#define __CONNECTION_HPP

#include <libsocket/inetserverstream.hpp>
#include "memory_manager.hpp"

class ConnectionManager;

using namespace std;
using libsocket::inet_stream;

class Connection
{
protected:
    int _socketFd = 0;
    inet_stream * _stream = nullptr;
    ConnectionManager * _parent;

public:
    Connection(int socketFd, inet_stream * stream, ConnectionManager * parent)
    : _socketFd(socketFd), _stream(stream), _parent(parent)
    {}

    virtual ~Connection();

    virtual void HandleData(Block * block) = 0;
};


class TelnetConnection : public Connection
{
protected:
    string ExtractCommand(const string&);
public:
    class CommandParseException : public std::exception
    {  
    };

    TelnetConnection(int socketFd, inet_stream * stream, ConnectionManager * parent)
    : Connection(socketFd, stream, parent)
    {}

    ~TelnetConnection() = default;

    void HandleData(Block * block) override;
};

#endif
