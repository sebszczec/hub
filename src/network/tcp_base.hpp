#ifndef __TCP_CONNECTION_STORATE_HPP
#define __TCP_CONNECTION_STORATE_HPP

#include <vector>
#include <memory>
#include <string>
#include "tcp_connection.hpp"

namespace network
{
    class TcpBase
    {
    private:
        static unsigned int _instanceIndexGenerator;
        
        std::vector<std::shared_ptr<TcpConnection>> _connections;
        std::string _serverName;
        unsigned int _instanceIndex;
        bool _ssl = false;        

    protected:
    public:
        TcpBase(std::string serverName, bool ssl)
        : _serverName(serverName), 
        _instanceIndex(TcpBase::_instanceIndexGenerator++),
        _ssl(ssl)
        {
        }

        const std::vector<std::shared_ptr<TcpConnection>> & GetConnections();
        void AddConnection(std::shared_ptr<TcpConnection> connection);
        void RemoveConnection(std::shared_ptr<TcpConnection> connection);
        void ClearConnections();
        std::string GetLoggingPrefix() const;
        bool IsSSL() const;

    };
} // namespave network
#endif // __TCP_CONNECTION_STORATE_HPP
