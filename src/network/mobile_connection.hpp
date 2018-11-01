#ifndef __MOBILE_CONNECTION_HPP
#define __MOBILE_CONNECTION_HPP

#include <boost/asio/ssl.hpp>
#include "tcp_connection.hpp"

namespace network
{

class WrongPacketSizeException : public std::exception
{
};

class MobileConnection : public TcpConnection
{
private:

public:
    MobileConnection(boost::asio::io_service& ios, TcpBase & parent, boost::asio::ssl::context & sslContext)
    : TcpConnection(ios, parent, sslContext)
    {}

    void HandleData();
};

} // namespace network

#endif // __MOBILE_CONNECTION_HPP
