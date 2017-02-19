#ifndef __CONNECTION_HPP
#define __CONNECTION_HPP

#include <libsocket/inetserverstream.hpp>
#include "memory_manager.hpp"

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

    virtual ~Connection();

    virtual void HandleData(Block * block) = 0;
};


class TelnetConnection : public Connection
{
public:
    TelnetConnection(int socketFd, inet_stream * stream)
    : Connection(socketFd, stream)
    {}

    ~TelnetConnection() = default;

    void HandleData(Block * block) override;
};

#endif
