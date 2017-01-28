#include "telnet_server.hpp"
#include "logger.hpp"

TelnetServer::~TelnetServer()
{
    if (this->_server != nullptr)
    {
        delete this->_server;
        this->_server = nullptr;
    }
}

void TelnetServer::Start()
{
    Logger::Log("Starting TelnetServer");
    this->_server = new inet_stream_server(this->_host, this->_port, LIBSOCKET_IPv4);

    this->_readSet.add_fd(*(this->_server), LIBSOCKET_READ);

    this->_working = true;
    while (this->_working)
    {
        libsocket::selectset<inet_stream_server>::ready_socks readyPair;

        readyPair = this->_readSet.wait();

        Logger::Log("TelnetServer: new connection, proceeding..");
        auto socket = readyPair.first.back();
        readyPair.first.pop_back();

        if (socket->getfd() == this->_server->getfd())
        {
            Logger::Log("TelnetServer: new connection to sever, accepting..");
            inet_stream_server* server_socket = dynamic_cast<inet_stream_server*>(socket);
            auto connection = server_socket->accept2();
            *connection << "Welcome\n";
        }

    }
}

void TelnetServer::Stop()
{
    this->_working = false;

    if (this->_server != nullptr)
    {
        delete this->_server;
        this->_server = nullptr;
    }
}

