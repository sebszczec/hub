#ifndef __CONNECTION_MANAGER_HPP
#define __CONNECTION_MANAGER_HPP

#include <libsocket/inetserverstream.hpp>
#include <map>
#include <exception>
#include "iconnection.hpp"

using namespace std;
using libsocket::inet_stream;

namespace network
{

class ConnectionNotFoundException : public exception
{
};

class ConnectionManager
{
private:
    map<int, IConnection *> _connections;
public:

    ConnectionManager() = default;
    ~ConnectionManager() = default;

    template <typename CONNECTION_TYPE>
    void AddConnection(inet_stream & stream)
    {
        auto descriptor = stream.getfd();
        auto connection = new CONNECTION_TYPE(descriptor, &stream, this);

        this->_connections[descriptor] = connection;
    }

    void RemoveConnection(int socketFd);
    IConnection * GetConnection(int socketFd);
    map<int, IConnection *> & GetConnections();
    void ClearAllConnections();
    unsigned int  GetNumberOfConnections();
};

} // namespace network

#endif