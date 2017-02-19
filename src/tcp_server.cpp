#include "tcp_server.hpp"
#include "logger.hpp"
#include <sstream>
#include <chrono>
#include <thread>
#include "configuration_manager.hpp"
#include "memory_manager.hpp"

int TelnetServer::_idGenerator = 0;
map<int, TelnetServer *> TelnetServer::_instances;

TelnetServer::~TelnetServer()
{
    this->Stop();

    auto item = TelnetServer::_instances.find(this->_id);
    TelnetServer::_instances.erase(item);
}

void TelnetServer::AddStream()
{
    auto stream = this->_server->accept();
    auto descriptor = stream->getfd();
                
    Logger::LogDebug(this->_prefix + ": new connection to sever, accepting fd: " + std::to_string(descriptor));
    this->_readSet.add_fd(*stream, LIBSOCKET_READ);
    this->_connectionManager.AddConnection(stream);

    *stream << "Welcome\n";
}

void TelnetServer::RemoveStream(const inet_stream& stream)
{
    auto descriptor = stream.getfd();
    Logger::LogDebug(this->GetExtendedPrefix(descriptor) + ": client disconnected");
    this->_readSet.remove_fd(stream);
    this->_connectionManager.RemoveConnection(descriptor);
}

void TelnetServer::Start()
{    
    Logger::Log(this->_prefix + ": starting on port " + this->_port);
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
            Logger::LogDebug(this->_prefix + ": new trigger, proceeding");

            auto socket = readyPair.first.back();
            readyPair.first.pop_back();

            if (socket->getfd() == this->_server->getfd())
            {
                this->AddStream();
            }
            else
            {
                auto block = MemoryManager::GetInstance()->GetFreeBlock();
                char * buffer = reinterpret_cast<char *>(block->GetPayload());
                auto stream = dynamic_cast<inet_stream *>(socket);
                auto socketFd = stream->getfd();

                auto bytes = stream->rcv(buffer, 128);
                if (bytes > 0)
                {                    
                    std::stringstream temp_stream;
                    for(int i = 0; i< bytes; ++i)
                        temp_stream << " " << std::hex << (int)buffer[i];
                    string data = temp_stream.str();

                    Logger::LogDebug(this->GetExtendedPrefix(socketFd) + ": new " + std::to_string(bytes) + " bytes of data:" + data);

                    string message(buffer, bytes - 2);
                    Logger::LogDebug(this->GetExtendedPrefix(socketFd) + ": " + message);

                    block->SetPayloadLength(bytes);
                    auto connection = this->_connectionManager.GetConnection(socketFd);
                    connection->HandleData(block);
                }
                else if (bytes == 0)
                {
                    this->RemoveStream(*stream);
                }
                else
                {
                    Logger::LogError(this->GetExtendedPrefix(socketFd) + ": something went wrong");
                }
            }
        }
    }

    Logger::LogDebug(this->_prefix + ": Out of the while() loop");
}

void TelnetServer::Stop()
{
    Logger::Log(this->_prefix + ": stopped ");

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
        this->_connectionManager.ClearAllConnections();
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
