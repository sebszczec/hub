#include "mobile_server.hpp"
#include "mobile_connection.hpp"

namespace network
{
    
const string MobileServer::Name = "Mobile";

MobileServer::MobileServer(ConnectionManager & connectionManager)
: _connectionManager(&connectionManager)
{

}

void MobileServer::AddConnection(inet_stream & stream)
{
    this->_connectionManager->AddConnection<MobileConnection>(stream);
}

void MobileServer::RemoveConnection(inet_stream & stream)
{
    auto descriptor = stream.getfd();
    this->_connectionManager->RemoveConnection(descriptor);
}

} // namespace network