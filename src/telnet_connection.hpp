#ifndef __TELNET_CONNECTION_HPP
#define __TELNET_CONNECTION_HPP

#include "iconnection.hpp"

class TelnetConnection : public IConnection
{
protected:
    bool ExtractCommand(const string&, string &);
public:
    class CommandParseException : public std::exception
    {  
    };

    TelnetConnection(int socketFd, inet_stream * stream, ConnectionManager * parent)
    : IConnection(socketFd, stream, parent)
    {}

    ~TelnetConnection() = default;

    void HandleData(Block * block) override;
};

#endif