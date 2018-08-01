#ifndef __MOBILE_SERVER_HPP
#define __MOBILE_SERVER_HPP

#include "connection_manager.hpp"
#include "libsocket/inetserverstream.hpp"
#include "libsocket/socket.hpp"

using libsocket::inet_stream;

namespace network
{

class MobileServer
{
private:
    ConnectionManager * _connectionManager;
public:
    MobileServer(ConnectionManager & connectionManager);
    ~MobileServer() = default;

    void AddConnection(inet_stream & stream);
    void RemoveConnection(inet_stream & stream);

    static const string Name;
};

} // namespace network

#endif
