#ifndef __TCP_SERVER_HPP
#define __TCP_SERVER_HPP

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include "system.hpp"
#include "tcp_base.hpp"

namespace network
{

using namespace machine;

class MissingSSLConfigurationException : public std::exception
{
private:
    string _message = "";

public:
    MissingSSLConfigurationException(string && message)
    : _message(message)
    {}

    virtual const char* what() const throw()
    {
        return _message.c_str();
    }
};

template <typename CONNECTION_TYPE>
class TcpServer : public TcpBase
{
private:
    boost::asio::io_context _ios;
    tcp::acceptor _acceptor;
    short _port;
    boost::asio::ssl::context _context;
    string _sslCrtFile = "";
    string _sslKeyFile = "";
    string _sslDhFile = "";
    string _sslPassword = "";

public:
    TcpServer(std::string serverName, short port, bool ssl)
    : TcpBase(serverName, ssl), _ios(), 
    _acceptor(_ios, tcp::endpoint(tcp::v4(), port)), 
    _port(port),
    _context(boost::asio::ssl::context::sslv23)
    {
    }

    void Run()
    {
        if (TcpBase::IsSSL())
        {
            if (this->_sslCrtFile.empty())
            {
                throw MissingSSLConfigurationException("SSL Server CRT file is not set");
            }

            if (this->_sslKeyFile.empty())
            {
                throw MissingSSLConfigurationException("SSL Server private Key file is not set");
            }

            if (this->_sslDhFile.empty())
            {
                throw MissingSSLConfigurationException("SSL Server DH file is not set");
            }

            if (this->_sslPassword.empty())
            {
                throw MissingSSLConfigurationException("SSL Server DH file is not set");
            }

            this->_context.set_options(
                boost::asio::ssl::context::default_workarounds
                | boost::asio::ssl::context::no_sslv2
                | boost::asio::ssl::context::single_dh_use);
            this->_context.set_password_callback(boost::bind(&TcpServer::GetPassword, this));
            this->_context.use_certificate_chain_file(this->_sslCrtFile);
            this->_context.use_private_key_file(this->_sslKeyFile, boost::asio::ssl::context::pem);
            this->_context.use_tmp_dh_file(this->_sslDhFile);

            System::GetLogger()->Log(this->GetLoggingPrefix() + ": SSL configured");
        }

        auto connection = std::make_shared<CONNECTION_TYPE>(this->_ios, *this, this->_context);  
        this->_acceptor.async_accept(connection->GetSocket(), boost::bind(&TcpServer::HandleAccept, this, connection, boost::asio::placeholders::error));

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

    void SetSSLServerCrtFile(string crtFile)
    {
        this->_sslCrtFile = crtFile;
    }

    void SetSSLServerKeyFile(string keyFile)
    {
        this->_sslKeyFile = keyFile;
    }

    void SetSSLServerDhFile(string dhFile)
    {
        this->_sslDhFile = dhFile;
    }

    void SetSSLPassword(string sslPassword)
    {
        this->_sslPassword = sslPassword;
    }

private:
    std::string GetPassword()
    {
        return this->_sslPassword;
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

        TcpBase::AddConnection(connection);
        connection->Start();

        connection = std::make_shared<CONNECTION_TYPE>(this->_ios, *this, this->_context);
        this->_acceptor.async_accept(connection->GetSocket(), boost::bind(&TcpServer::HandleAccept, this, connection, boost::asio::placeholders::error));       
    }
};

} // namespace network

#endif // __TCP_SERVER_HPP
