#ifndef __TCP_SERVER_HPP
#define __TCP_SERVER_HPP

#include <boost/asio.hpp>
#include "system.hpp"
#include "tcp_connection_storage.hpp"

namespace network
{

using namespace machine;

template <typename CONNECTION_TYPE>
class TcpServer : public TcpServerConnectionStorage
{
private:
    boost::asio::io_service _ios;
    tcp::acceptor _acceptor;
    short _port;

public:
    TcpServer(short port)
    : _ios(), _acceptor(_ios, tcp::endpoint(tcp::v4(), port)), _port(port)
    {
        auto connection = std::make_shared<CONNECTION_TYPE>(this->_ios, *this);
        
        this->_acceptor.async_accept(connection->GetSocket(), boost::bind(&TcpServer::HandleAccept, this, connection, boost::asio::placeholders::error));
    }

    void Run()
    {
        this->_ios.run();
    }

    void HandleAccept(std::shared_ptr<CONNECTION_TYPE> connection, const boost::system::error_code& err)
    {
        if (err) 
        {
            System::GetLogger()->LogError("TcpServer accept error: " + err.message());

            connection.reset();
            return;
        }

        connection->Start();
        TcpServerConnectionStorage::AddConnection(connection);

        connection = std::make_shared<CONNECTION_TYPE>(this->_ios, *this);
        this->_acceptor.async_accept(connection->GetSocket(), boost::bind(&TcpServer::HandleAccept, this, connection, boost::asio::placeholders::error));       
    }

    short GetPort()
    {
        return this->_port;
    }
};

} // namespace network

#endif // __TCP_SERVER_HPP
