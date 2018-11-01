#ifndef __TCP_CONNECTION_HPP
#define __TCP_CONNECTION_HPP

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/enable_shared_from_this.hpp>
#include "system.hpp"

namespace network
{

using boost::asio::ip::tcp;
typedef boost::asio::ssl::stream<boost::asio::ip::tcp::socket> ssl_socket;

class TcpBase;

class ClientSocket
{
private:
    tcp::socket _socket;
    ssl_socket _sslSocket;

public:
    ClientSocket(boost::asio::io_service& ios, boost::asio::ssl::context& context)
    : _socket(ios),
    _sslSocket(ios, context)
    {}

    tcp::socket & GetSocket()
    {
        return this->_socket;
    }

    ssl_socket & GetSSLSocket()
    {
        return this->_sslSocket;
    }
};

class TcpConnection : public std::enable_shared_from_this<TcpConnection>
{
protected:
    Context * _context = nullptr;
    machine::Block * _memoryBlock = nullptr;
    tcp::socket _socket;
    TcpBase & _parent;

    void HandleWrite(std::shared_ptr<TcpConnection>& connection, const boost::system::error_code& err, size_t bytesTransferred);
    void HandleRead(std::shared_ptr<TcpConnection>& connection, const boost::system::error_code& err, size_t bytesTransferred);
    
public:
    TcpConnection(boost::asio::io_service& ios, TcpBase & parent)
    : _context(machine::System::GetContextManager()->CreateContext()),
      _memoryBlock(machine::System::GetMemoryManager()->GetFreeBlock()), 
      _socket(ios),
      _parent(parent)
    {
    }

    virtual ~TcpConnection();

    virtual void Start();
    virtual void Stop();
    void SendData(const void * data, unsigned int size);
    
    virtual void HandleData() = 0;
    
    tcp::socket& GetSocket();
    Context & GetContext();
};

} // namespace network

#endif // __TCP_CONNECTION_HPP