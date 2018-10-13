#include "tcp_connection_storage.hpp"

namespace network
{
using namespace std;

void TcpServerConnectionStorage::AddConnection(shared_ptr<TcpConnection> connection)
{
    this->_connections.push_back(connection);
}

void TcpServerConnectionStorage::RemoveConnection(std::shared_ptr<TcpConnection> connection)
{
    auto position = std::find(this->_connections.begin(), this->_connections.end(), connection);
    if (position != _connections.end())
    {
        this->_connections.erase(position);
    }
}

const vector<shared_ptr<TcpConnection>> & TcpServerConnectionStorage::GetConnections()
{
    return this->_connections;
}

} // namespace network
