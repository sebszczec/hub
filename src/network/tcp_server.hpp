#ifndef __TCP_SERVER_HPP
#define __TCP_SERVER_HPP

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include "system.hpp"
#include "tcp_base.hpp"

namespace network
{

using namespace machine;

template <typename CONNECTION_TYPE>
class TcpServer : public TcpBase
{
private:
    boost::asio::io_service _ios;
    tcp::acceptor _acceptor;
    short _port;
    boost::asio::ssl::context _context;

public:
    TcpServer(std::string serverName, short port, bool ssl)
    : TcpBase(serverName, ssl), _ios(), 
    _acceptor(_ios, tcp::endpoint(tcp::v4(), port)), 
    _port(port),
    _context(boost::asio::ssl::context::sslv23)
    {
        if (TcpBase::IsSSL())
        {
            this->_context.set_options(
                boost::asio::ssl::context::default_workarounds
                | boost::asio::ssl::context::no_sslv2
                | boost::asio::ssl::context::single_dh_use);
            this->_context.set_password_callback(boost::bind(&TcpServer::GetPassword, this));
            this->_context.use_certificate_chain_file("server.crt");
            this->_context.use_private_key_file("server.key", boost::asio::ssl::context::pem);
            this->_context.use_tmp_dh_file("dh512.pem");

            System::GetLogger()->Log(this->GetLoggingPrefix() + ": SSL configured");
        }

        auto connection = std::make_shared<CONNECTION_TYPE>(this->_ios, *this, this->_context);        
        this->_acceptor.async_accept(connection->GetSocket(), boost::bind(&TcpServer::HandleAccept, this, connection, boost::asio::placeholders::error));
    }

    void Run()
    {
        System::GetLogger()->Log(this->GetLoggingPrefix() + ": started");
        this->_ios.run();
    }

    void Stop()
    {
        System::GetLogger()->Log(this->GetLoggingPrefix() + ": stopped");
        _ios.post(boost::bind(&TcpServer::HandleStop, this));
    }

    short GetPort()
    {
        return this->_port;
    }

private:
    std::string GetPassword()
    {
        return "Test";
    }

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

        connection = std::make_shared<CONNECTION_TYPE>(this->_ios, *this, this->_context);
        this->_acceptor.async_accept(connection->GetSocket(), boost::bind(&TcpServer::HandleAccept, this, connection, boost::asio::placeholders::error));       
    }
};

} // namespace network

#endif // __TCP_SERVER_HPP
