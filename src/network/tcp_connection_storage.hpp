#ifndef __TCP_CONNECTION_STORATE_HPP
#define __TCP_CONNECTION_STORATE_HPP

#include <vector>
#include <memory>
#include "tcp_connection.hpp"

namespace network
{
    class TcpServerConnectionStorage
    {
    private:
        std::vector<std::shared_ptr<TcpConnection>> _connections;

    protected:
        void AddConnection(std::shared_ptr<TcpConnection> connection);

    public:
        const std::vector<std::shared_ptr<TcpConnection>> & GetConnections();
    };
} // namespave network
#endif // __TCP_CONNECTION_STORATE_HPP
