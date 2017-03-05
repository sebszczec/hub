#ifndef __TELNET_SERVER_HPP
#define __TELNET_SERVER_HPP

#include "connection_manager.hpp"
#include <libsocket/inetserverstream.hpp>
#include <libsocket/socket.hpp>

using libsocket::inet_stream;

class TelnetServer
{
public:
    TelnetServer() = default;

    void AddConnection(ConnectionManager & manager, inet_stream & stream);
    void RemoveConnection(ConnectionManager & manager, inet_stream & stream);
};

#endif
