#ifndef __MOBILE_CONNECTION_HPP
#define __MOBILE_CONNECTION_HPP

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
    MobileConnection(boost::asio::io_service& ios, TcpBase & parent)
    : TcpConnection(ios, parent)
    {}

    void HandleData();
};

} // namespace network

#endif // __MOBILE_CONNECTION_HPP
