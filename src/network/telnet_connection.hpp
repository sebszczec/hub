#ifndef __TELNET_CONNECTION_HPP
#define __TELNET_CONNECTION_HPP

#include "iconnection.hpp"
#include "icommand.hpp"

using commands::CommandArgument;

namespace network
{

class TelnetConnection : public IConnection
{
protected:
    bool ExtractCommand(const string&, string &, CommandArgument & arg);
    void ExtractParameters(const string&, CommandArgument & arg);

public:
    class CommandParseException : public std::exception
    {  
    };

    TelnetConnection(int socketFd, inet_stream * stream, ConnectionManager * parent)
    : IConnection(socketFd, stream, parent)
    {}

    ~TelnetConnection() = default;

    void HandleData(machine::Block * block) override;
};

} // namespace network

#endif