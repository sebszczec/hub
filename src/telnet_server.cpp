#include "telnet_server.hpp"

TelnetServer::TelnetServer(const string& port)
: TcpServer(port)
{
    // TcpServer::OnAddConnection.AddMethod([]()
    //     {
            
    //     });
}