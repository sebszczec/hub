#include "telnet_server.hpp"
#include "logger.hpp"
#include <sstream>

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
    Logger::Log("TelnetServer: starting, port: " + this->_port);
    this->_server = new inet_stream_server(this->_host, this->_port, LIBSOCKET_IPv4);

    //this->_serverReadSet.add_fd(*(this->_server), LIBSOCKET_READ);
    this->_testReadSet.add_fd(*(this->_server), LIBSOCKET_READ);

    this->_working = true;
    while (this->_working)
    {
        // libsocket::selectset<inet_stream_server>::ready_socks readyPair;
        libsocket::selectset<inet_socket>::ready_socks readyPair;

        // readyPair = this->_serverReadSet.wait(1);
        readyPair = this->_testReadSet.wait();

        while(!readyPair.first.empty())
        {
            Logger::LogDebug("TelnetServer: new connection, proceeding..");
            auto socket = readyPair.first.back();
            readyPair.first.pop_back();

            if (socket->getfd() == this->_server->getfd())
            {
                Logger::LogDebug("TelnetServer: new connection to sever, accepting..");
                auto connection = this->_server->accept();
                this->_testReadSet.add_fd(*connection, LIBSOCKET_READ);

                *connection << "Welcome\n";
            }
            else
            {
                char buffer[128] = {0};
                auto connection = dynamic_cast<inet_stream *>(socket);
                
                auto bytes = connection->rcv(buffer, 128);
                if (bytes > 0)
                {
                    std::stringstream temp_stream;
                    for(int i = 0; i< bytes; ++i)
                        temp_stream << std::hex << (int)buffer[i] << " ";
                    string data = temp_stream.str();

                    Logger::LogDebug("TelnetServer: new " + std::to_string(bytes) + " bytes of data: " + data);
                }
                else
                {
                    Logger::LogDebug("TelnetServer: client disconnected");
                    this->_testReadSet.remove_fd(*connection);
                }
            }
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

