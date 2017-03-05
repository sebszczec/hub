#include "telnet_server.hpp"
#include "telnet_connection.hpp"

TelnetServer::TelnetServer(const string& port)
: TcpServer(port)
{
    DelegateArgument arg;
    TcpServer::OnAddConnection.AddMethod([](DelegateArgument & argument)
    {
        auto tcpSeverArg = reinterpret_cast<TcpServerDelegateArgument *>(&argument);
        auto connectionManager = tcpSeverArg->GetSender()->GetConnectionManager();
        auto stream = tcpSeverArg->GetStream();

        connectionManager.AddConnection<TelnetConnection>(*stream);
        *stream << "Welcome\n";

    }, arg);
}