#include "telnet_server.hpp"
#include "telnet_connection.hpp"

void TelnetServer::AddConnection(ConnectionManager & manager, inet_stream & stream)
{
    manager.AddConnection<TelnetConnection>(stream);
    stream << "Welcome\n";
}

void TelnetServer::RemoveConnection(ConnectionManager & manager, inet_stream & stream)
{
    auto descriptor = stream.getfd();
    manager.RemoveConnection(descriptor);
}