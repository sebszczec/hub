#ifndef __TELNET_SERVER_HPP
#define __TELNET_SERVER_HPP

#include "connection_manager.hpp"
#include <libsocket/inetserverstream.hpp>
#include <libsocket/socket.hpp>

using libsocket::inet_stream;

namespace network
{

class TelnetServer
{
private:
    ConnectionManager * _connectionManager;
public:
    TelnetServer(ConnectionManager & connectionManager);

    void AddConnection(inet_stream & stream);
    void RemoveConnection(inet_stream & stream);
};

} // namespace networok

#endif