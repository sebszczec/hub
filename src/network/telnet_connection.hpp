#ifndef __TELNET_CONNECTION_HPP
#define __TELNET_CONNECTION_HPP

#include "tcp_connection.hpp"

namespace network
{

class TelnetConnection : public TcpConnection
{
private:

public:
    TelnetConnection(boost::asio::io_service& ios, TcpBase & parent)
    : TcpConnection(ios, parent)
    {}

    void Start() override;
    void ExtractParameters(const string &message, commands::CommandArgument & arg);
    bool ExtractCommand(const string& message, string & result, commands::CommandArgument & arg);
    void HandleData() override;
};

} // namespace network

#endif // __TELNET_CONNECTION_HPP
