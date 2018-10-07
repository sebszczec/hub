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
#include "mobile_messages.hpp"
#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/bind.hpp>

using namespace network;
using namespace machine;

using boost::asio::ip::tcp;

class BoostTcpConnection;

class BoostTcpServerConnectionStorage
{
private:
    vector<shared_ptr<BoostTcpConnection>> _connections;

protected:
    void AddConnection(shared_ptr<BoostTcpConnection> connection)
    {
        this->_connections.push_back(connection);
    }

public:
    const vector<shared_ptr<BoostTcpConnection>> & GetConnections()
    {
        return this->_connections;
    }
};

template <typename CONNECTION_TYPE>
class BoostTcpServer : public BoostTcpServerConnectionStorage
{
private:
    boost::asio::io_service& _ios;
    tcp::acceptor _acceptor;
    short _port;

public:
    BoostTcpServer(boost::asio::io_service& ios, short port)
    : _ios(ios), _acceptor(ios, tcp::endpoint(tcp::v4(), port)), _port(port)
    {
        auto connection = std::make_shared<CONNECTION_TYPE>(ios, *this);
        
        this->_acceptor.async_accept(connection->GetSocket(), boost::bind(&BoostTcpServer::HandleAccept, this, connection, boost::asio::placeholders::error));
    }

    void HandleAccept(std::shared_ptr<CONNECTION_TYPE> connection, const boost::system::error_code& err)
    {
        if (err) 
        {
            System::GetLogger()->LogError("TcpServer accept error: " + err.message());

            connection.reset();
            return;
        }

        connection->Start();
        BoostTcpServerConnectionStorage::AddConnection(connection);

        connection = std::make_shared<CONNECTION_TYPE>(this->_ios, *this);
        this->_acceptor.async_accept(connection->GetSocket(), boost::bind(&BoostTcpServer::HandleAccept, this, connection, boost::asio::placeholders::error));       
    }

    short GetPort()
    {
        return this->_port;
    }
};

class BoostTcpConnection : public std::enable_shared_from_this<BoostTcpConnection>
{
protected:
    Context * _context = nullptr;
    machine::Block * _memoryBlock = nullptr;
    tcp::socket _socket;
    BoostTcpServerConnectionStorage & _parent;
    
public:
    BoostTcpConnection(boost::asio::io_service& ios, BoostTcpServerConnectionStorage & parent)
    : _context(machine::System::GetContextManager()->CreateContext()),
      _memoryBlock(machine::System::GetMemoryManager()->GetFreeBlock()), 
      _socket(ios),
      _parent(parent)
    {
    }

    virtual ~BoostTcpConnection()
    {
        machine::System::GetContextManager()->DeleteContext(this->_context);

        if (this->_memoryBlock)
        {
            machine::System::GetMemoryManager()->DeleteBlock(this->_memoryBlock);
            this->_memoryBlock = nullptr; 
        }
    }

    virtual void Start()
    {
        char * buffer = reinterpret_cast<char *>(this->_memoryBlock->GetPayload());

        this->_socket.async_read_some(boost::asio::buffer(buffer, this->_memoryBlock->GetMaxSize()),
            boost::bind(&BoostTcpConnection::HandleRead, this, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred)
        );
    }

    void SendData(const void * data, unsigned int size)
    {
        boost::asio::async_write(this->_socket, boost::asio::buffer(data, size), boost::bind(&BoostTcpConnection::HandleWrite, shared_from_this(), boost::asio::placeholders::error, 
            boost::asio::placeholders::bytes_transferred));
    }

    void HandleWrite(const boost::system::error_code& err, size_t bytesTransferred)
    {
        (void)bytesTransferred;

        if (err)
        {
             System::GetLogger()->LogError("TcpConnection HandleWrite error: " + err.message());
        }
    }

    virtual void HandleData() = 0;

    void HandleRead(std::shared_ptr<BoostTcpConnection>& connection, const boost::system::error_code& err, size_t bytesTransferred)
    {
        if (err)
        {
            System::GetLogger()->LogError("TcpConnection HandleRead error: " + err.message());
            machine::System::GetMemoryManager()->DeleteBlock(this->_memoryBlock);
            this->_memoryBlock = nullptr;
            return;
        }

        this->_memoryBlock->SetPayloadLength(bytesTransferred);
        this->HandleData();

        char * buffer = reinterpret_cast<char *>(this->_memoryBlock->GetPayload());

        this->_socket.async_read_some(boost::asio::buffer(buffer, this->_memoryBlock->GetMaxSize()),
            boost::bind(&BoostTcpConnection::HandleRead, this, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred)
        );
    }

    tcp::socket& GetSocket()
    {
        return this->_socket;
    }
};

class BoostMobileConnection : public BoostTcpConnection
{
private:

public:
    BoostMobileConnection(boost::asio::io_service& ios, BoostTcpServerConnectionStorage & parent)
    : BoostTcpConnection(ios, parent)
    {}

    void HandleData()
    {
        auto logger = machine::System::GetLogger();
        logger->LogDebug("MobileConnection: Received data block");

        auto packetLength = this->_memoryBlock->GetPayloadLength();
        if (packetLength != network::NetworkMessageSize)
        {
            logger->LogError("MobileConnection: Wrong network packet size: " + std::to_string(packetLength));
            throw WrongPacketSizeException();
            return; 
        }

        auto networkMessage = reinterpret_cast<NetworkMessage *>(this->_memoryBlock->GetPayload());

        switch (networkMessage->ID)
        {
            case network::MessageId::HandshakeRequest:
            logger->Log("MobileConnection: HandshakeRequest received");
            break;

            default:
            logger->LogError("MobileConnection: Unknown network message ID: " + std::to_string(networkMessage->ID));
            break;
        }
    }
};

class BoostTelnetConnection : public BoostTcpConnection
{
private:

public:
    BoostTelnetConnection(boost::asio::io_service& ios, BoostTcpServerConnectionStorage & parent)
    : BoostTcpConnection(ios, parent)
    {}

    void Start()
    {
        BoostTcpConnection::Start();

        std::string message = "Welcome\n";
        this->SendData(message.c_str(), message.size());
    }

    void ExtractParameters(const string &message, CommandArgument & arg)
    {
        auto position = message.find(' ');
        auto tempPos = 0;

        while (position != string::npos)
        {
            arg.Args.push_back(message.substr(tempPos, position - tempPos));
            tempPos = position + 1;
            position = message.find(' ', tempPos);
        }

        // and the last one
        position = message.find('\r', tempPos);
        if (position != string::npos)
        {
            arg.Args.push_back(message.substr(tempPos, position - tempPos));
        }
    }

    bool ExtractCommand(const string& message, string & result, CommandArgument & arg)
    {
        auto position = message.find(' ');
        if (position == string::npos)
        {
            position = message.find('\r');
        }

        if (position == string::npos)
        {
            return false;
        }

        result = message.substr(0, position);
        this->ExtractParameters(message.substr(position + 1, message.size() - 1), arg);
        return true;
    }

    void HandleData() override
    {
        auto logger = System::GetLogger();

        auto length = this->_memoryBlock->GetPayloadLength();
        if (length == 0)
        {
            logger->LogError("TelnetConnection: memory block is empty");
            return;
        }

        char * payload = reinterpret_cast<char *>(this->_memoryBlock->GetPayload());
        string message(payload, length);

        if (message[0] == '.')
        {
            string command = "";
            commands::CommandExecutionResult result;
            commands::CommandArgument arg;

            if (!this->ExtractCommand(message, command, arg))
            {
                logger->LogError("TelnetConnection: cannot extract command from " + message);
                return;
            }

            logger->LogDebug("TelnetConnection: got command " + command);

            arg.Context = this->_context;
            string message;
            if (System::GetCommandManager()->ExecuteCommand(command, arg, result))
            {
                logger->LogDebug("TelnetConnection: command execution result: " + result.Result);
                message = command + ": " + result.Result + "\n";
            }
            else
            {
                message = command + ": " + result.ErrorMessage + "\n";
            }

            this->SendData(reinterpret_cast<const void *>(message.c_str()), message.size());
            return;
        }

        // send message to others
        logger->LogDebug("TelnetConnection: sending to other users: " + message.substr(0, message.length() - 1));
        auto & connections = this->_parent.GetConnections();

        for (auto & item : connections)
        {
            if (item == shared_from_this())
            {
                continue;
            }

            item->SendData(reinterpret_cast<const void *>(message.c_str()), message.size());
        }
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
    BoostTcpServer<BoostTelnetConnection> server(ios, System::GetConfigurationManager()->GetResource(CMV::TelnetPort).ToInt());
    
    tools::Worker boostServerWorker(false);
    boostServerWorker.StartAsync([&ios] () {ios.run();});

    boost::asio::io_service ios2;
    BoostTcpServer<BoostMobileConnection> server2(ios2, System::GetConfigurationManager()->GetResource(CMV::MobilePort).ToInt());
    
    tools::Worker boostServerWorker2(false);
    boostServerWorker2.StartAsync([&ios2] () {ios2.run();});

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

