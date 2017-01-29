#include "telnet_server.hpp"
#include "logger.hpp"
#include <sstream>
#include <chrono>
#include <thread>
#include "configuration_manager.hpp"

int TelnetServer::_idGenerator = 0;
map<int, TelnetServer *> TelnetServer::_instances;

TelnetServer::~TelnetServer()
{
    this->Stop();

    auto item = TelnetServer::_instances.find(this->_id);
    TelnetServer::_instances.erase(item);
}

void TelnetServer::Start()
{    
    Logger::Log("TelnetServer[" + std::to_string(this->_id) + "]: port: " + this->_port);
    this->_server = new inet_stream_server(this->_host, this->_port, LIBSOCKET_IPv4);
    this->_readSet.add_fd(*(this->_server), LIBSOCKET_READ);

    using CM = ConfigurationManager;
    using CMV = CM::Variable;
    long long delay = CM::GetResource(CMV::TelnetPooling).ToInt();

    this->_working = true;
    while (this->_working)
    {
        libsocket::selectset<inet_socket>::ready_socks readyPair;

        readyPair = this->_readSet.wait(delay);

        while(!readyPair.first.empty())
        {
            Logger::LogDebug("TelnetServer[" + std::to_string(this->_id) + "]: new connection, proceeding..");
            auto socket = readyPair.first.back();
            readyPair.first.pop_back();

            if (socket->getfd() == this->_server->getfd())
            {
                Logger::LogDebug("TelnetServer: id: " + std::to_string(this->_id) + ", new connection to sever, accepting..");
                auto connection = this->_server->accept();
                this->_readSet.add_fd(*connection, LIBSOCKET_READ);

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

                    Logger::LogDebug("TelnetServer[" + std::to_string(this->_id) + "]: new " + std::to_string(bytes) + " bytes of data: " + data);

                    string message(buffer, bytes - 2);
                    Logger::LogDebug("TelnetServer[" + std::to_string(this->_id) + "]: " + message);
                }
                else
                {
                    Logger::LogDebug("TelnetServer[" + std::to_string(this->_id) + "]: client disconnected");
                    this->_readSet.remove_fd(*connection);
                }
            }
        }
    }

    Logger::LogDebug("TelnetServer[" + std::to_string(this->_id) + "]: Out of the while() loop");
}

void TelnetServer::Stop()
{
    Logger::Log("TelnetServer[" + std::to_string(this->_id) + "]: stopped ");

    using CM = ConfigurationManager;
    using CMV = CM::Variable;
    int delay = CM::GetResource(CMV::TelnetCooling).ToInt();
    
    this->_working = false;
    using DelayMS = std::chrono::duration<int, std::milli>;
    auto sleepTime = DelayMS(delay);
    this_thread::sleep_for(sleepTime);

    if (this->_server != nullptr)
    {
        this->_readSet.remove_fd(*(this->_server));
        this->_server->destroy();
        delete this->_server;
        this->_server = nullptr;
    }
}


void TelnetServer::StopAllInstances()
{
    for (auto & pair : TelnetServer::_instances)
    {
        auto & instance = pair.second;
        instance->Stop();
    }
}
