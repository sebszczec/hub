#ifndef __TCP_SSL_SERVER_HPP
#define __TCP_SSL_SERVER_HPP

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include "system.hpp"
#include "tcp_base.hpp"

namespace network
{

using namespace machine;

template <typename CONNECTION_TYPE>
class TcpSSLServer : public TcpBase
{
private:
    boost::asio::io_service _ios;
    tcp::acceptor _acceptor;
    short _port;

public:
    TcpSSLServer(std::string serverName, short port)
    : TcpBase(serverName), _ios(), _acceptor(_ios, tcp::endpoint(tcp::v4(), port)), _port(port)
    {
        auto connection = std::make_shared<CONNECTION_TYPE>(this->_ios, *this);
        
        this->_acceptor.async_accept(connection->GetSocket(), boost::bind(&TcpSSLServer::HandleAccept, this, connection, boost::asio::placeholders::error));
    }

    void Run()
    {
        System::GetLogger()->Log(this->GetLoggingPrefix() + ": started");
        this->_ios.run();
    }

    void Stop()
    {
        System::GetLogger()->Log(this->GetLoggingPrefix() + ": stopped");
        _ios.post(boost::bind(&TcpSSLServer::HandleStop, this));
    }

    short GetPort()
    {
        return this->_port;
    }

private:
    void HandleStop()
    {
        this->_acceptor.cancel();
        this->_acceptor.close();

        auto & connections = TcpBase::GetConnections();
        for (auto connection : connections)
        {
            connection->Stop();
        }
        
        TcpBase::ClearConnections();
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
        TcpBase::AddConnection(connection);

        connection = std::make_shared<CONNECTION_TYPE>(this->_ios, *this);
        this->_acceptor.async_accept(connection->GetSocket(), boost::bind(&TcpSSLServer::HandleAccept, this, connection, boost::asio::placeholders::error));       
    }
};

} // namespace network

#endif // __TCP_SSL_SERVER_HPP
