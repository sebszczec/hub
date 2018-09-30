#include "daemon.hpp"
#include <stdlib.h>
#include <unistd.h>
#include "system.hpp"
#include "configuration_manager.hpp"
#include "worker.hpp"
#include "timer.hpp"
#include "signal_handler.hpp"
#include "tcp_server.hpp"
#include "telnet_server.hpp"
#include "mobile_server.hpp"
#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/bind.hpp>

using namespace network;
using namespace machine;

using boost::asio::ip::tcp;
class BoostTcpConnection : public std::enable_shared_from_this<BoostTcpConnection>
{
private:
    tcp::socket _socket;
    machine::Block * _memoryBlock = nullptr;
public:
    BoostTcpConnection(boost::asio::io_service& ios)
    : _socket(ios), _memoryBlock(machine::System::GetMemoryManager()->GetFreeBlock())
    {
    }

    void Start()
    {
        char * buffer = reinterpret_cast<char *>(this->_memoryBlock->GetPayload());

        this->_socket.async_read_some(boost::asio::buffer(buffer, this->_memoryBlock->GetMaxSize()),
            boost::bind(&BoostTcpConnection::HandleRead, this, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred)
        );
    }

    void HandleWrite(const boost::system::error_code& err, size_t bytesTransferred)
    {
        // error handling 
        (void)err;
        (void)bytesTransferred;
    }

    void HandleRead(std::shared_ptr<BoostTcpConnection>& connection, const boost::system::error_code& err, size_t bytesTransferred)
    {
        if (err)
        {
            std::cerr << "err (recv): " << err.message() << std::endl;
            machine::System::GetMemoryManager()->DeleteBlock(this->_memoryBlock);
            return;
        }

        this->_memoryBlock->SetPayloadLength(bytesTransferred);
        char * buffer = reinterpret_cast<char *>(this->_memoryBlock->GetPayload());
        // handle data
        {
            string message(buffer, this->_memoryBlock->GetPayloadLength());
            string response = "Response to: " + message;

            boost::asio::async_write(this->_socket, boost::asio::buffer(response), boost::bind(&BoostTcpConnection::HandleWrite, shared_from_this(), boost::asio::placeholders::error, 
                boost::asio::placeholders::bytes_transferred));
        }

        this->_socket.async_read_some(boost::asio::buffer(buffer, this->_memoryBlock->GetMaxSize()),
            boost::bind(&BoostTcpConnection::HandleRead, this, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred)
        );
    }

    tcp::socket& GetSocket()
    {
        return this->_socket;
    }
};

class BoostTcpServer
{
private:
    boost::asio::io_service& _ios;
    tcp::acceptor _acceptor;
    short _port;
public:
    BoostTcpServer(boost::asio::io_service& ios, short port)
    : _ios(ios), _acceptor(ios, tcp::endpoint(tcp::v4(), port)), _port(port)
    {
        auto connection = std::make_shared<BoostTcpConnection>(ios);
        
        this->_acceptor.async_accept(connection->GetSocket(), boost::bind(&BoostTcpServer::HandleAccept, this, connection, boost::asio::placeholders::error));
    }

    void HandleAccept(std::shared_ptr<BoostTcpConnection> connection, const boost::system::error_code& err)
    {
        if (err) 
        {
            std::cerr << "err: " + err.message() << std::endl;
            connection.reset();
            return;
        }

        connection->Start();
        connection = std::make_shared<BoostTcpConnection>(this->_ios);
        this->_acceptor.async_accept(connection->GetSocket(), boost::bind(&BoostTcpServer::HandleAccept, this, connection, boost::asio::placeholders::error));       
    }

    short GetPort()
    {
        return this->_port;
    }

};

int main()
{
    using CM = ConfigurationManager;
    using CMV = CM::Variable;

    if (!System::Start())
    {
        exit(EXIT_FAILURE);
    }

    // Worker worker(true, Worker::DelayMS(500));
    // worker.StartAsync([](){
    //     Logger::LogDebug("Keep alive message from worker.");
    // });

    // Timer timer(Worker::DelayMS(500), true);
    // timer.StartAsync([](){
    //     Logger::LogDebug("Keep alive message from timer.");
    // });

    boost::asio::io_service ios;
    BoostTcpServer server(ios, 9000);
    
    tools::Worker boostServerWorker(false);
    boostServerWorker.StartAsync([&ios] () {ios.run();});

    TcpServer<TelnetServer> telnetServer(System::GetConfigurationManager()->GetResource(CMV::TelnetPort).ToString());
    tools::Worker telnetWorker(false);
    telnetWorker.StartAsync([&telnetServer] () { telnetServer.Start(); });

    TcpServer<MobileServer> mobileServer(System::GetConfigurationManager()->GetResource(CMV::MobilePort).ToString());
    tools::Worker mobileWorker(false);
    mobileWorker.StartAsync([&mobileServer] () { mobileServer.Start(); });

    /* The Big Loop */
    auto logger = System::GetLogger();
    while (true) 
    {
        /* Do some task here ... */  
        logger->LogDebug("Standard loop");  
        sleep(1); /* wait 1 second */
    }

   exit(EXIT_SUCCESS);
}

