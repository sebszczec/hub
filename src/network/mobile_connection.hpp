#ifndef __MOBILE_CONNECTION_HPP
#define __MOBILE_CONNECTION_HPP

#include "iconnection.hpp"

namespace network
{

class MobileConnection : public IConnection
{
public:
    MobileConnection(int socketFd, inet_stream * stream, ConnectionManager * parent)
    : IConnection(socketFd, stream, parent)
    {}

    ~MobileConnection() = default;

    void HandleData(machine::Block * block) override;

};

} // namespace network

#endif