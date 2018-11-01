#include "tcp_connection.hpp"
#include <boost/bind.hpp>
#include "tcp_base.hpp"
#include <iostream>

namespace network
{

using namespace machine;

TcpConnection::~TcpConnection()
{
    machine::System::GetContextManager()->DeleteContext(this->_context);

    if (this->_memoryBlock)
    {
        machine::System::GetMemoryManager()->DeleteBlock(this->_memoryBlock);
        this->_memoryBlock = nullptr; 
    }
}

void TcpConnection::Start()
{
    char * buffer = reinterpret_cast<char *>(this->_memoryBlock->GetPayload());

    this->_socket.async_read_some(
        boost::asio::buffer(buffer, this->_memoryBlock->GetMaxSize()),
        boost::bind(&TcpConnection::HandleRead, this, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred)
    );
}

void TcpConnection::Stop()
{
    this->_socket.close();
}

void TcpConnection::SendData(const void * data, unsigned int size)
{
    boost::asio::async_write(
        this->_socket, 
        boost::asio::buffer(data, size), 
        boost::bind(&TcpConnection::HandleWrite,
        this, 
        shared_from_this(), 
        boost::asio::placeholders::error, 
        boost::asio::placeholders::bytes_transferred)
    );
}

void TcpConnection::HandleWrite(std::shared_ptr<TcpConnection>& connection, const boost::system::error_code& err, size_t bytesTransferred)
{
    (void)bytesTransferred;

    if (err)
    {
        auto id = std::to_string(connection->GetContext().GetId());
        auto prefix = this->_parent.GetLoggingPrefix();

        System::GetLogger()->LogError(prefix + "[" + id +  "]: HandleWrite error: " + err.message());
    }
}

void TcpConnection::HandleRead(std::shared_ptr<TcpConnection>& connection, const boost::system::error_code& err, size_t bytesTransferred)
{
    if (err)
    {
        auto id = std::to_string(connection->GetContext().GetId());
        auto prefix = this->_parent.GetLoggingPrefix();

        System::GetLogger()->LogError(prefix + "[" + id +  "]: HandleRead error: " + err.message());
        machine::System::GetMemoryManager()->DeleteBlock(this->_memoryBlock);
        this->_memoryBlock = nullptr;
        
        this->Stop();
        this->_parent.RemoveConnection(shared_from_this());
                
        return;
    }

    this->_memoryBlock->SetPayloadLength(bytesTransferred);
    this->HandleData();

    char * buffer = reinterpret_cast<char *>(this->_memoryBlock->GetPayload());

    this->_socket.async_read_some(
        boost::asio::buffer(buffer, this->_memoryBlock->GetMaxSize()),
        boost::bind(&TcpConnection::HandleRead, this, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred)
    );
}

tcp::socket& TcpConnection::GetSocket()
{
    return this->_socket;
}

Context & TcpConnection::GetContext()
{
    return *this->_context;
}

} // namespace network
