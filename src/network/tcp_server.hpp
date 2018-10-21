#ifndef __TCP_SERVER_HPP
#define __TCP_SERVER_HPP

#include <boost/asio.hpp>
#include "system.hpp"
#include "tcp_connection_storage.hpp"

namespace network
{

using namespace machine;

template <typename CONNECTION_TYPE>
class TcpServer : public TcpConnectionStorage
{
private:
    boost::asio::io_service _ios;
    tcp::acceptor _acceptor;
    short _port;

public:
    TcpServer(std::string serverName, short port)
    : TcpConnectionStorage(serverName), _ios(), _acceptor(_ios, tcp::endpoint(tcp::v4(), port)), _port(port)
    {
        auto connection = std::make_shared<CONNECTION_TYPE>(this->_ios, *this);
        
        this->_acceptor.async_accept(connection->GetSocket(), boost::bind(&TcpServer::HandleAccept, this, connection, boost::asio::placeholders::error));
    }

    void Run()
    {
        System::GetLogger()->LogError(this->GetLoggingPrefix() + ": started");
        this->_ios.run();
    }

    void Stop()
    {
        System::GetLogger()->LogError(this->GetLoggingPrefix() + ": stopped");
        _ios.post(boost::bind(&TcpServer::HandleStop, this));
    }

    short GetPort()
    {
        return this->_port;
    }

private:
    void HandleStop()
    {
        this->_acceptor.stop();

        auto & connections = TcpConnectionStorage::GetConnections();
        for (auto connection : connections)
        {
            connection->Stop();
        }
        
        TcpConnectionStorage::ClearConnections();
    }

    void HandleAccept(std::shared_ptr<CONNECTION_TYPE> connection, const boost::system::error_code& err)
    {
        if (err) 
        {
            System::GetLogger()->LogError(this->GetLoggingPrefix() + ": accept error: " + err.message());

            connection.reset();
            return;
        }

        connection->Start();
        TcpConnectionStorage::AddConnection(connection);

        connection = std::make_shared<CONNECTION_TYPE>(this->_ios, *this);
        this->_acceptor.async_accept(connection->GetSocket(), boost::bind(&TcpServer::HandleAccept, this, connection, boost::asio::placeholders::error));       
    }
};

} // namespace network

#endif // __TCP_SERVER_HPP
