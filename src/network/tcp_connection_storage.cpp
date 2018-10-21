#include "tcp_connection_storage.hpp"
#include "logger.hpp"

using namespace machine;

namespace network
{
using namespace std;

unsigned int TcpConnectionStorage::_instanceIndexGenerator = 0;

void TcpConnectionStorage::AddConnection(shared_ptr<TcpConnection> connection)
{
    auto id = std::to_string(connection->GetContext().GetId());
    System::GetLogger()->Log(this->GetLoggingPrefix() + "[" + id + "]: TcpConnection connected");
    this->_connections.push_back(connection);
}

void TcpConnectionStorage::RemoveConnection(std::shared_ptr<TcpConnection> connection)
{
    auto id = std::to_string(connection->GetContext().GetId());
    auto position = std::find(this->_connections.begin(), this->_connections.end(), connection);
    if (position != _connections.end())
    {
        System::GetLogger()->Log(this->GetLoggingPrefix() + "[" + id + "]: TcpConnection disconnected");
        this->_connections.erase(position);
        return;
    }

    System::GetLogger()->LogError(this->GetLoggingPrefix() + "[" + id + "]: TcpConnection disconnect error, connection does not exist");
}

const vector<shared_ptr<TcpConnection>> & TcpConnectionStorage::GetConnections()
{
    return this->_connections;
}

std::string TcpConnectionStorage::GetLoggingPrefix()
{
    return "Server<" + this->_serverName + ">[" + std::to_string(this->_instanceIndex) + "]";
}

} // namespace network
