#ifndef __TCP_CONNECTION_STORATE_HPP
#define __TCP_CONNECTION_STORATE_HPP

#include <vector>
#include <memory>
#include <string>
#include "tcp_connection.hpp"

namespace network
{
    class TcpConnectionStorage
    {
    private:
        static unsigned int _instanceIndexGenerator;
        
        std::vector<std::shared_ptr<TcpConnection>> _connections;
        std::string _serverName;
        unsigned int _instanceIndex;        

    protected:

    public:
        TcpConnectionStorage(std::string serverName)
        : _serverName(serverName), _instanceIndex(TcpConnectionStorage::_instanceIndexGenerator++)
        {
        }

        const std::vector<std::shared_ptr<TcpConnection>> & GetConnections();
        void AddConnection(std::shared_ptr<TcpConnection> connection);
        void RemoveConnection(std::shared_ptr<TcpConnection> connection);
        std::string GetLoggingPrefix();
    };
} // namespave network
#endif // __TCP_CONNECTION_STORATE_HPP
