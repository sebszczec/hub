#include "tcp_base.hpp"
#include "logger.hpp"

using namespace machine;

namespace network
{
using namespace std;

unsigned int TcpBase::_instanceIndexGenerator = 0;

void TcpBase::AddConnection(shared_ptr<TcpConnection> connection)
{
    auto id = std::to_string(connection->GetContext().GetId());
    System::GetLogger()->Log(this->GetLoggingPrefix() + "[" + id + "]: TcpConnection connected");
    this->_connections.push_back(connection);
}

void TcpBase::RemoveConnection(std::shared_ptr<TcpConnection> connection)
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

const vector<shared_ptr<TcpConnection>> & TcpBase::GetConnections()
{
    return this->_connections;
}

std::string TcpBase::GetLoggingPrefix() const
{
    return "Server<" + this->_serverName + ">[" + std::to_string(this->_instanceIndex) + "]";
}

void TcpBase::ClearConnections() 
{
    this->_connections.clear();
}

bool TcpBase::IsSSL() const
{
    return this->_ssl;
}

} // namespace network
