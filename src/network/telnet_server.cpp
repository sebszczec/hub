#include "telnet_server.hpp"
#include "telnet_connection.hpp"

namespace network
{

const string TelnetServer::Name = "Telnet";

TelnetServer::TelnetServer(ConnectionManager & connectionManager)
: _connectionManager(&connectionManager)
{

}

void TelnetServer::AddConnection(inet_stream & stream)
{
    this->_connectionManager->AddConnection<TelnetConnection>(stream);
    stream << "Welcome\n";
}

void TelnetServer::RemoveConnection(inet_stream & stream)
{
    auto descriptor = stream.getfd();
    this->_connectionManager->RemoveConnection(descriptor);
}

} // namespace network
