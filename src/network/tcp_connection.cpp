#include "tcp_connection.hpp"
#include <boost/bind.hpp>
#include "tcp_base.hpp"
#include <iostream>

namespace network
{

using namespace machine;

TcpConnection::TcpConnection(boost::asio::io_context& ios, TcpBase & parent, boost::asio::ssl::context & sslContext)
: _context(machine::System::GetContextManager()->CreateContext()),
    _memoryBlock(machine::System::GetMemoryManager()->GetFreeBlock()), 
    _socket(ios, sslContext),
    _parent(parent)
{
    if (this->_parent.IsSSL())
    {
        this->_socket.SetSSLflag(true);
    }
}

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

    if (this->_parent.IsSSL())
    {

        // blocking handshake. i.e. stopping telnet from broadcasting
        try
        {
            this->_socket.GetSSLSocket().handshake(boost::asio::ssl::stream_base::server);
        }
        catch (boost::system::system_error & error)
        {
            auto id = std::to_string(this->GetContext().GetId());
            auto prefix = this->_parent.GetLoggingPrefix();

            System::GetLogger()->LogError(prefix + "[" + id +  "]: HandleHandShake error: " + error.what());
            this->Stop();
            this->_parent.RemoveConnection(shared_from_this());

            return;
        }

        this->_socket.GetSSLSocket().async_read_some(
            boost::asio::buffer(buffer, this->_memoryBlock->GetMaxSize()),
            boost::bind(&TcpConnection::HandleRead, this, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred)
        );

        return;
    }

    // standard non-SSL connection handling
    this->_socket.GetTcpSocket().async_read_some(
        boost::asio::buffer(buffer, this->_memoryBlock->GetMaxSize()),
        boost::bind(&TcpConnection::HandleRead, this, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred)
    );
}

void TcpConnection::Stop()
{
    if (this->_socket.IsSSL())
    {
        //this->_socket.GetSSLSocket().shutdown();    
    }
    this->_socket.GetLowestLayerSocket().close();
}

void TcpConnection::SendData(const void * data, unsigned int size)
{
    if (this->_socket.IsSSL())
    {
        boost::asio::async_write(
            this->_socket.GetSSLSocket(), 
            boost::asio::buffer(data, size), 
            boost::bind(&TcpConnection::HandleWrite,
                this, 
                shared_from_this(), 
                boost::asio::placeholders::error, 
                boost::asio::placeholders::bytes_transferred)
        );

        return;
    }

    // standard non-SSL connection handling
    boost::asio::async_write(
        this->_socket.GetTcpSocket(), 
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

    if (this->_socket.IsSSL())
    {
        this->_socket.GetSSLSocket().async_read_some(
            boost::asio::buffer(buffer, this->_memoryBlock->GetMaxSize()),
            boost::bind(&TcpConnection::HandleRead, this, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred)
        );

        return;
    }

    // standard non-SSL connection handling
    this->_socket.GetTcpSocket().async_read_some(
        boost::asio::buffer(buffer, this->_memoryBlock->GetMaxSize()),
        boost::bind(&TcpConnection::HandleRead, this, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred)
    );
}

boost::asio::ip::tcp::socket::lowest_layer_type & TcpConnection::GetSocket()
{
    return this->_socket.GetLowestLayerSocket();
}

Context & TcpConnection::GetContext()
{
    return *this->_context;
}

} // namespace network
