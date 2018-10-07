#include "tcp_connection_storage.hpp"

namespace network
{
using namespace std;

void TcpServerConnectionStorage::AddConnection(shared_ptr<TcpConnection> connection)
{
    this->_connections.push_back(connection);
}

const vector<shared_ptr<TcpConnection>> & TcpServerConnectionStorage::GetConnections()
{
    return this->_connections;
}

} // namespace network
